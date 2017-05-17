#include "kdlTypekit.hpp"

template class RTT::internal::DataSource< ::KDL::Chain >;
template class RTT::internal::AssignableDataSource< ::KDL::Chain >;
template class RTT::internal::ValueDataSource< ::KDL::Chain >;
template class RTT::internal::ConstantDataSource< ::KDL::Chain >;
template class RTT::internal::ReferenceDataSource< ::KDL::Chain >;
template class RTT::base::ChannelElement< ::KDL::Chain >;
template class RTT::OutputPort< ::KDL::Chain >;
template class RTT::InputPort< ::KDL::Chain >;
template class RTT::Property< ::KDL::Chain >;
template class RTT::Attribute< ::KDL::Chain >;

namespace KDL{
  using namespace std;
  using namespace RTT;

  void loadChainTypes(){
    RTT::types::Types()->addType( new KDLTypeInfo<Chain>("KDL.Chain") );
    RTT::types::Types()->addType( new SequenceTypeInfo<std::vector< Chain > >("KDL.Chain[]") );
    RTT::types::Types()->addType( new CArrayTypeInfo<RTT::types::carray< Chain > >("KDL.cChain[]") );
  }
}  
