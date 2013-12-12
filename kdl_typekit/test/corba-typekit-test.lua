require 'rttlib'
require 'os'

local lc=rtt.getTC()
local dp=lc:getPeer("Deployer")

if not dp:import("kdl_typekit") then 
   print("Failed to import kdl_typekit")
   os.exit(1)
end

if not dp:loadComponent("testcomponent","CORBA") then
   print("Failed to create proxy for \"testcomponent\"")
   os.exit(1)
end
local tc=dp:getPeer("testcomponent")

---VectorTests---
function test_vector(tc)

   local v1=rtt.Variable("KDL.Vector")
   v1:fromtab{X=1.,Y=2.,Z=3.}
   local v2=rtt.Variable("KDL.Vector")
   v2:fromtab{X=3.,Y=2.,Z=1.}
   local v3=rtt.Variable("KDL.Vector")
   v3:fromtab{X=4.,Y=5.,Z=6.}
   if not v1 or not v2 or not v3 then
      print("Failed to create KDL.Vector variable")
      return false
   end

   --Set Property
   local prop = tc:getProperty("vectorProperty")
   if not prop then
      print("Failed to retrieve vectorProperty")
      return false
   end
   
   if not prop:set(v1) or v1 ~= prop:get()then
      print("Failed to set vectorProperty")
      return false
   end

   --Call vector operation (return current value of prop as return value and sets argument as new value)
   local op = tc:getOperation("vectorOperation")
   if not op then
      print("Failed to get vectorOperation")
      return false
   end
   local v4 = op(v2)
   if v4 ~= v1 then
      print("vectorOperation failed, expected: "..v1..", actual: "..v3)
      return false
   end
   
   --write new value to port, will set current value of prop to outport and prop to new value
   local wport = rttlib.port_clone_conn(tc:getPort("VectorIn"))
   local rport = rttlib.port_clone_conn(tc:getPort("VectorOut"))
   if not wport or not rport then
      print("Failed to connect to VectorIn or VectorOut port")
      return false
   end
   if not wport:write(v3) then
      print("Failed to write vector to port")
      return false
   end

   --wait for remote to handle write
   os.execute('sleep 1')
   local fs,v5 = rport:read()
   if fs ~= 'NewData' then
      print("Failed to read vector from port")
      return false
   end
   
   --Check if read value equals last value of property:
   if v5 ~= v2 then
      print("vector port write/read failed, expected: "..v2..", actual: "..v5)
      return false
   end
   --Check if current value of property is the written value:
   local v6 = prop.get()
   if v3 ~= v6 then
      print("Failed to write value, expected: "..v3..", actual: "..v6)
      return false
   end
   
end

if not pcall(test_vector(tc)) then
   print("Vector tests failed")
   os.exit(1)
else
   print("Vector tests succeeded")
   os.exit(0)
end

