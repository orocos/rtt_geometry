#include "kdlTypekit.hpp"

template class RTT::internal::DataSource< ::KDL::Joint >;
template class RTT::internal::AssignableDataSource< ::KDL::Joint >;
template class RTT::internal::ValueDataSource< ::KDL::Joint >;
template class RTT::internal::ConstantDataSource< ::KDL::Joint >;
template class RTT::internal::ReferenceDataSource< ::KDL::Joint >;
template class RTT::base::ChannelElement< ::KDL::Joint >;
template class RTT::OutputPort< ::KDL::Joint >;
template class RTT::InputPort< ::KDL::Joint >;
template class RTT::Property< ::KDL::Joint >;
template class RTT::Attribute< ::KDL::Joint >;

namespace KDL{
  using namespace std;
  using namespace RTT;

  void loadJointTypes(){
    RTT::types::Types()->addType( new KDLTypeInfo<Joint>("KDL.Joint") );
    RTT::types::Types()->addType( new SequenceTypeInfo<std::vector< Joint > >("KDL.Joint[]") );
    RTT::types::Types()->addType( new CArrayTypeInfo<RTT::types::carray< Joint > >("KDL.cJoint[]") );
  }
}  
