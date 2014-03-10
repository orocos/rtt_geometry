#!/usr/bin/env rttlua-corba-gnulinux

require 'luaunit'
require 'rttlib'
require 'os'

TestKDLCorbaTypekit = {} --TestClass

function TestKDLCorbaTypekit:setUp()
   --Start server
   os.execute("./setupcomponent.ops -d")
   --Wait for server to startup
   os.execute("sleep 3")
   self.lc=rtt.getTC()
   self.dp=self.lc:getPeer("Deployer")

   assertEquals(true,self.dp:import("kdl_typekit"))
   assertEquals(true,self.dp:loadComponent("testcomponent","CORBA"))
   self.tc=self.dp:getPeer("testcomponent")
end

---VectorTests---
function TestKDLCorbaTypekit:test_vector()

   local v1=rtt.Variable("KDL.Vector")
   v1:fromtab{X=1.,Y=2.,Z=3.}
   local v2=rtt.Variable("KDL.Vector")
   v2:fromtab{X=3.,Y=2.,Z=1.}
   local v3=rtt.Variable("KDL.Vector")
   v3:fromtab{X=4.,Y=5.,Z=6.}

   --Set Property
   local prop=self.tc:getProperty("vectorProperty")
   prop:set(v1)
   assertEquals(prop:get(),v1)

   --Call vector operation (return current value of prop as return value and sets argument as new value)
   local op = self.tc:getOperation("vectorOperation")

   local v4 = op(v2)
   assertEquals(v4,v1)
   
   --write new value to port, will set current value of prop to outport and prop to new value
   local wport = rtt.OutputPort("KDL.Vector")
   local rport = rtt.InputPort("KDL.Vector")
   self.lc:addPort(wport,"VectorOut","")
   self.lc:addPort(rport,"VectorIn","")
   assertEquals(true,rport:connect(self.tc:getPort("VectorOut")))
   assertEquals(true,wport:connect(self.tc:getPort("VectorIn")))

   assertEquals(true,wport:info()['connected'])
   assertEquals(true,rport:info()['connected'])
   wport:write(v3)

   --wait for remote to handle write
   os.execute('sleep 1')
   local v5 = rtt.Variable("KDL.Vector")
   assertEquals(rport:read(v5),'NewData')
   
   --Check if read value equals last value of property:
   assertEquals(v5,v2)
   --Check if current value of property is the written value:
   local v6 = prop:get()
   assertEquals(v6,v3)
end

function TestKDLCorbaTypekit:tearDown()
   self.dp:shutdown()
   rttlib.tc_cleanup()
   os.execute('pkill -f setupcomponent.ops')
end

LuaUnit:run()