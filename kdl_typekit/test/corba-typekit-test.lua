require 'rttlib'
require 'os'

local lc=rtt.getTC()
local dp=lc:getPeer("Deployer")

if not dp:import("kdl_typekit") then 
   print("Failed to import kdl_typekit")
   error()
end

if not dp:loadComponent("testcomponent","CORBA") then
   print("Failed to create proxy for \"testcomponent\"")
   error()
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
      error()
   end

   --Set Property
   local prop = tc:getProperty("vectorProperty")
   if not prop then
      print("Failed to retrieve vectorProperty")
      error()
   end
   
   if not prop:set(v1) or v1 ~= prop:get()then
      print("Failed to set vectorProperty")
      error()
   end

   --Call vector operation (return current value of prop as return value and sets argument as new value)
   local op = tc:getOperation("vectorOperation")
   if not op then
      print("Failed to get vectorOperation")
      error()
   end
   local v4 = op(v2)
   if v4 ~= v1 then
      print("vectorOperation failed, expected: "..tostring(v1)..", actual: "..tostring(v3))
      error()
   end
   
   --write new value to port, will set current value of prop to outport and prop to new value
   local wport = rtt.OutputPort("KDL.Vector")
   local rport = rtt.InputPort("KDL.Vector")
   lc:addPort(wport,"VectorOut","")
   lc:addPort(rport,"VectorIn","")
   rport:connect(tc:getPort("VectorOut")) 
   wport:connect(tc:getPort("VectorIn"))

   if not wport:info()['connected'] or not rport:info()['connected'] then
      print("Failed to connect to VectorIn or VectorOut port")
      error()
   end

   wport:write(v3)

   --wait for remote to handle write
   os.execute('sleep 1')
   local fs,v5 = rport:read()
   if fs ~= 'NewData' then
      print("Failed to read vector from port")
      error()
   end
   
   --Check if read value equals last value of property:
   if v5 ~= v2 then
      print("vector port write/read failed, expected: "..tostring(v2)..", actual: "..tostring(v5))
      error()
   end
   --Check if current value of property is the written value:
   local v6 = prop:get()
   if v3 ~= v6 then
      print("Failed to write value, expected: "..tostring(v3)..", actual: "..tostring(v6))
      error()
   end
end

if pcall(function() test_vector(tc) end) then
   print("Vector tests succeeded")
   rttlib.tc_cleanup()
else
   print("Vector tests failed")
   rttlib.tc_cleanup()
end
