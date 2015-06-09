#include "kdlTypekit.hpp"

template class RTT::internal::DataSource< ::KDL::Segment >;
template class RTT::internal::AssignableDataSource< ::KDL::Segment >;
template class RTT::internal::ValueDataSource< ::KDL::Segment >;
template class RTT::internal::ConstantDataSource< ::KDL::Segment >;
template class RTT::internal::ReferenceDataSource< ::KDL::Segment >;
template class RTT::base::ChannelElement< ::KDL::Segment >;
template class RTT::OutputPort< ::KDL::Segment >;
template class RTT::InputPort< ::KDL::Segment >;
template class RTT::Property< ::KDL::Segment >;
template class RTT::Attribute< ::KDL::Segment >;

namespace KDL{
  using namespace std;
  using namespace RTT;

  void loadSegmentTypes(){
    RTT::types::Types()->addType( new KDLTypeInfo<Segment>("KDL.Segment") );
    RTT::types::Types()->addType( new SequenceTypeInfo<std::vector< Segment > >("KDL.Segment[]") );
  };
}  
