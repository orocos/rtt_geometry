#include <gtest/gtest.h>
#include <rtt/os/main.h>
#include <rtt/plugin/PluginLoader.hpp>
#include <rtt/scripting/ScriptingService.hpp>
#include <rtt/TaskContext.hpp>


void throw_function() {
    throw std::exception();
}

class KDLPluginScriptingTest : public testing::Test {

protected:
    KDLPluginScriptingTest():
        tc("test")
    {
    }

    virtual void SetUp() {
        ASSERT_TRUE(RTT::plugin::PluginLoader::Instance()->loadTypekit("kdl_typekit",RTT::plugin::PluginLoader::Instance()->getPluginPath())) << "Failed to load kdl typekit";
        ASSERT_TRUE(tc.loadService("scripting")) << "Unable to load scripting service";
        scripting = boost::dynamic_pointer_cast<RTT::scripting::ScriptingService>( tc.provides()->getService("scripting") );
        ASSERT_TRUE(scripting) << "Failed to get loaded scripting service";

        tc.addOperation("throw",&throw_function);
        tc.setPeriod(0.01);
        ASSERT_TRUE(scripting->loadPrograms("./typekit-test.ops",false)) << "Failed to load test program";
        ASSERT_TRUE(tc.start()) << "Failed to start TaskContext";
    }
    virtual void TearDown() {
    }
    
    RTT::TaskContext tc;
    RTT::scripting::ScriptingService::shared_ptr scripting;
};

TEST_F(KDLPluginScriptingTest, ScriptTest) {
    RTT::scripting::ProgramInterfacePtr program = scripting->getProgram("vector_test");
    ASSERT_TRUE(program) << "Failed to get program";
    ASSERT_TRUE(program->start());
    while(program->isRunning()) {;
        ASSERT_FALSE(program->inError()) << "program failed on line " << program->getLineNumber();
        usleep(1000);
    }
    ASSERT_FALSE(program->inError()) << "Failed on line " << program->getLineNumber();
}

int ORO_main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

