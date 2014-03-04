#include <kdl/frames.hpp>
#include <rtt/RTT.hpp>
#include <rtt/Component.hpp>

using namespace RTT;
using namespace KDL;
using namespace std;

class KDLTypekitTestComponent : public TaskContext{
private:
    OutputPort<Vector>   port_vector_out;
    OutputPort<Rotation> port_rotation_out;
    OutputPort<Frame>    port_frame_out;
    OutputPort<Wrench>   port_wrench_out;
    OutputPort<Twist>    port_twist_out;

    InputPort<Vector>   port_vector_in;
    InputPort<Rotation> port_rotation_in;
    InputPort<Frame>    port_frame_in;
    InputPort<Wrench>   port_wrench_in;
    InputPort<Twist>    port_twist_in;

    Vector   prop_vector;
    Rotation prop_rotation;
    Frame    prop_frame;
    Wrench   prop_wrench;
    Twist    prop_twist;

    Vector vectorOperation(const Vector& vector_in)
    {
        Vector vector_tmp=prop_vector;
        prop_vector=vector_in;
        return vector_tmp;
    }
    
    Rotation rotationOperation(const Rotation& rotation_in)
    {
        Rotation rotation_tmp=prop_rotation;
        prop_rotation=rotation_in;
        return rotation_tmp;
    }

    Frame frameOperation(const Frame& frame_in)
    {
        Frame frame_tmp=prop_frame;
        prop_frame=frame_in;
        return frame_tmp;
    }

    Wrench wrenchOperation(const Wrench& wrench_in)
    {
        Wrench wrench_tmp=prop_wrench;
        prop_wrench=wrench_in;
        return wrench_tmp;
    }
    
    Twist twistOperation(const Twist& twist_in)
    {
        Twist twist_tmp=prop_twist;
        prop_twist=twist_in;
        return twist_tmp;
    }

public:
    KDLTypekitTestComponent(const string& name) : TaskContext(name)
    {
        this->addPort("VectorOut",   port_vector_out);
        this->addPort("RotationOut", port_rotation_out);
        this->addPort("FrameOut",    port_frame_out);
        this->addPort("WrenchOut",   port_wrench_out);
        this->addPort("TwistOut",    port_twist_out);

        this->addEventPort("VectorIn",   port_vector_in);
        this->addEventPort("RotationIn", port_rotation_in);
        this->addEventPort("FrameIn",    port_frame_in);
        this->addEventPort("WrenchIn",   port_wrench_in);
        this->addEventPort("TwistIn",    port_twist_in);

        this->addOperation("vectorOperation",   &KDLTypekitTestComponent::vectorOperation,  this);
        this->addOperation("rotationOperation", &KDLTypekitTestComponent::rotationOperation,this);
        this->addOperation("frameOperation",    &KDLTypekitTestComponent::frameOperation,   this);
        this->addOperation("wrenchOperation",   &KDLTypekitTestComponent::wrenchOperation,  this);
        this->addOperation("twistOperation",    &KDLTypekitTestComponent::twistOperation,   this);

        this->addProperty("vectorProperty",   prop_vector);
        this->addProperty("rotationProperty", prop_rotation);
        this->addProperty("frameProperty",    prop_frame);
        this->addProperty("wrenchProperty",   prop_wrench);
        this->addProperty("twistProperty",    prop_twist);
    }

    void updateHook()
    {
        KDL::Vector tmp_vector;
        if(port_vector_in.read(tmp_vector)==NewData){
            port_vector_out.write(prop_vector);
            prop_vector = tmp_vector;
        }

        KDL::Rotation tmp_rotation;
        if(port_rotation_in.read(tmp_rotation)==NewData){
            port_rotation_out.write(prop_rotation);
            prop_rotation = tmp_rotation;
        }

        KDL::Frame tmp_frame;
        if(port_frame_in.read(tmp_frame)==NewData){
            port_frame_out.write(prop_frame);
            prop_frame = tmp_frame;
        }

        KDL::Wrench tmp_wrench;
        if(port_wrench_in.read(tmp_wrench)==NewData){
            port_wrench_out.write(prop_wrench);
            prop_wrench = tmp_wrench;
        }

        KDL::Twist tmp_twist;
        if(port_twist_in.read(tmp_twist)==NewData){
            port_twist_out.write(prop_twist);
            prop_twist = tmp_twist;
        }

        return;
    }

};

ORO_CREATE_COMPONENT(KDLTypekitTestComponent)
