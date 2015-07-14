#include "kdlTypekit.hpp"

template class RTT::internal::DataSource< ::KDL::Vector >;
template class RTT::internal::AssignableDataSource< ::KDL::Vector >;
template class RTT::internal::ValueDataSource< ::KDL::Vector >;
template class RTT::internal::ConstantDataSource< ::KDL::Vector >;
template class RTT::internal::ReferenceDataSource< ::KDL::Vector >;
template class RTT::base::ChannelElement< ::KDL::Vector >;
template class RTT::OutputPort< ::KDL::Vector >;
template class RTT::InputPort< ::KDL::Vector >;
template class RTT::Property< ::KDL::Vector >;
template class RTT::Attribute< ::KDL::Vector >;
template class RTT::internal::DataSource< std::vector<KDL::Vector> >;
template class RTT::internal::AssignableDataSource< std::vector<KDL::Vector> >;
template class RTT::internal::ValueDataSource< std::vector<KDL::Vector> >;
template class RTT::internal::ConstantDataSource< std::vector<KDL::Vector> >;
template class RTT::internal::ReferenceDataSource< std::vector<KDL::Vector> >;
template class RTT::base::ChannelElement< std::vector<KDL::Vector> >;
template class RTT::OutputPort< std::vector<KDL::Vector> >;
template class RTT::InputPort< std::vector<KDL::Vector> >;
template class RTT::Property< std::vector<KDL::Vector> >;
template class RTT::Attribute< std::vector<KDL::Vector> >;

namespace KDL{
  using namespace std;
  using namespace RTT;

  void loadVectorTypes(){
    RTT::types::Types()->addType( new KDLVectorTypeInfo<Vector,3>("KDL.Vector") );
    RTT::types::Types()->addType( new SequenceTypeInfo<std::vector< Vector > >("KDL.Vector[]") );
  };
}  
