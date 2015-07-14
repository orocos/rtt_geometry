#include "kdlTypekit.hpp"

template class RTT::internal::DataSource< ::KDL::Wrench >;
template class RTT::internal::AssignableDataSource< ::KDL::Wrench >;
template class RTT::internal::ValueDataSource< ::KDL::Wrench >;
template class RTT::internal::ConstantDataSource< ::KDL::Wrench >;
template class RTT::internal::ReferenceDataSource< ::KDL::Wrench >;
template class RTT::base::ChannelElement< KDL::Wrench >;
template class RTT::OutputPort< ::KDL::Wrench >;
template class RTT::InputPort< ::KDL::Wrench >;
template class RTT::Property< ::KDL::Wrench >;
template class RTT::Attribute< ::KDL::Wrench >;
template class RTT::internal::DataSource< std::vector<KDL::Wrench> >;
template class RTT::internal::AssignableDataSource< std::vector<KDL::Wrench> >;
template class RTT::internal::ValueDataSource< std::vector<KDL::Wrench> >;
template class RTT::internal::ConstantDataSource< std::vector<KDL::Wrench> >;
template class RTT::internal::ReferenceDataSource< std::vector<KDL::Wrench> >;
template class RTT::base::ChannelElement< std::vector<KDL::Wrench> >;
template class RTT::OutputPort< std::vector<KDL::Wrench> >;
template class RTT::InputPort< std::vector<KDL::Wrench> >;
template class RTT::Property< std::vector<KDL::Wrench> >;
template class RTT::Attribute< std::vector<KDL::Wrench> >;

namespace KDL{
  using namespace std;
  using namespace RTT;

  void loadWrenchTypes(){
    RTT::types::Types()->addType( new KDLVectorTypeInfo<Wrench,6>("KDL.Wrench") );
    RTT::types::Types()->addType( new SequenceTypeInfo<std::vector< Wrench > >("KDL.Wrench[]") );
  };
}  
