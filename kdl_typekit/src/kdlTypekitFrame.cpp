#include "kdlTypekit.hpp"

template class RTT::internal::DataSource< ::KDL::Frame >;
template class RTT::internal::AssignableDataSource< ::KDL::Frame >;
template class RTT::internal::ValueDataSource< ::KDL::Frame >;
template class RTT::internal::ConstantDataSource< ::KDL::Frame >;
template class RTT::internal::ReferenceDataSource< ::KDL::Frame >;
template class RTT::base::ChannelElement< ::KDL::Frame >;
template class RTT::OutputPort< ::KDL::Frame >;
template class RTT::InputPort< ::KDL::Frame >;
template class RTT::Property< ::KDL::Frame >;
template class RTT::Attribute< ::KDL::Frame >;
template class RTT::internal::DataSource< std::vector<KDL::Frame> >;
template class RTT::internal::AssignableDataSource< std::vector<KDL::Frame> >;
template class RTT::internal::ValueDataSource< std::vector<KDL::Frame> >;
template class RTT::internal::ConstantDataSource< std::vector<KDL::Frame> >;
template class RTT::internal::ReferenceDataSource< std::vector<KDL::Frame> >;
template class RTT::base::ChannelElement< std::vector<KDL::Frame> >;
template class RTT::OutputPort< std::vector<KDL::Frame> >;
template class RTT::InputPort< std::vector<KDL::Frame> >;
template class RTT::Property< std::vector<KDL::Frame> >;
template class RTT::Attribute< std::vector<KDL::Frame> >;

namespace KDL{
  using namespace std;
  using namespace RTT;

  void loadFrameTypes(){
    RTT::types::Types()->addType( new KDLTypeInfo<Frame>("KDL.Frame") );
    RTT::types::Types()->addType( new SequenceTypeInfo<std::vector< Frame > >("KDL.Frame[]") );
    RTT::types::Types()->addType( new CArrayTypeInfo<RTT::types::carray< Frame > >("KDL.cFrame[]") );
  }

}  
