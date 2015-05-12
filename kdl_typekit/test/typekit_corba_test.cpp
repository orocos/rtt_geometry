#include <stdlib.h>

#include <gtest/gtest.h>
#include <ocl/CorbaDeploymentComponent.hpp>
#include <rtt/os/main.h>
#include <rtt/TaskContext.hpp>
#include <rtt/transports/corba/TaskContextServer.hpp>

#include "kdlTypekitTypes.hpp"

class KDLCORBAPluginTest : public testing::Test {

protected:
    OCL::CorbaDeploymentComponent depl;
    RTT::TaskContext* tc;

    KDLCORBAPluginTest():
        depl("Deployer"), tc(0)
    {}

    virtual void SetUp() {
        //Start server
        system("./setupcomponent.ops -d");
        // Wait for server to startup
        sleep(3);
        //Setup corba
        ASSERT_TRUE(RTT::corba::TaskContextServer::InitOrb( 0,0 )) << "Failed to bring up CORBA";
        RTT::corba::TaskContextServer::ThreadOrb();
        ASSERT_TRUE(depl.import("kdl_typekit"));
        ASSERT_TRUE(depl.loadComponent("testcomponent","CORBA"));

        tc = 0;
        tc = depl.getPeer("testcomponent");
        ASSERT_FALSE(tc == 0);
    }
    virtual void TearDown(){
        depl.shutdownDeployment();
        RTT::corba::TaskContextServer::ShutdownOrb();
        RTT::corba::TaskContextServer::DestroyOrb();
        system("pkill -f setupcomponent.ops");
    }
};

TEST_F(KDLCORBAPluginTest, VectorTest) {

   KDL::Vector v1(1.,2.,3.);
   KDL::Vector v2(3.,2.,1.);
   KDL::Vector v3(4.,5.,6.);

   //Set remote property
   RTT::Property<KDL::Vector>* prop = tc->properties()->getPropertyType<KDL::Vector>("vectorProperty");
   ASSERT_FALSE (prop == 0);
   prop->set(v1);
   EXPECT_EQ(prop->get(),v1) << "Failed to set remote KDL::Vector property";

   // Call vector operation (return current value of prop as return value and sets argument as new value)
   RTT::OperationCaller<KDL::Vector (const KDL::Vector& vector_in)> op = tc->getOperation("vectorOperation");
   KDL::Vector v4 = op(v2);
   EXPECT_EQ(v4,v1) << "Failed to call remote operation with KDL type";

   //Write new value to port, will set current value of prop to outport and prop to new value
   RTT::OutputPort<KDL::Vector> wport;
   RTT::InputPort<KDL::Vector> rport;
   depl.addPort(wport);
   depl.addPort(rport);
   ASSERT_TRUE(wport.connectTo(tc->getPort("VectorIn")) && wport.connected()) << "Failed to connect to remote input port";
   ASSERT_TRUE(rport.connectTo(tc->getPort("VectorOut")) && rport.connected()) << "Failed to connect to remote output port";

   wport.write(v3);
   //wait for remote to handle write
   sleep(1);
   KDL::Vector v5;
   ASSERT_EQ(rport.read(v5),RTT::NewData) << "Failed to read data from port";

   //Check if read value equals last value of property:
   EXPECT_EQ(v5,v2) << "Failed to read KDL Vector from port";
   //Check if current value of property is the written value:
   KDL::Vector v6 = prop->get();
   EXPECT_EQ(v6,v3) << "Failed to write KDL Vector to port";
}

int ORO_main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

