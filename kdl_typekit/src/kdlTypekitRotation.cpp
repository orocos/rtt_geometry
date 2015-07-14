#include "kdlTypekit.hpp"

template class RTT::internal::DataSource< ::KDL::Rotation >;
template class RTT::internal::AssignableDataSource< ::KDL::Rotation >;
template class RTT::internal::ValueDataSource< ::KDL::Rotation >;
template class RTT::internal::ConstantDataSource< ::KDL::Rotation >;
template class RTT::internal::ReferenceDataSource< ::KDL::Rotation >;
template class RTT::base::ChannelElement< ::KDL::Rotation >;
template class RTT::OutputPort< ::KDL::Rotation >;
template class RTT::InputPort< ::KDL::Rotation >;
template class RTT::Property< ::KDL::Rotation >;
template class RTT::Attribute< ::KDL::Rotation >;
template class RTT::internal::DataSource< std::vector<KDL::Rotation> >;
template class RTT::internal::AssignableDataSource< std::vector<KDL::Rotation> >;
template class RTT::internal::ValueDataSource< std::vector<KDL::Rotation> >;
template class RTT::internal::ConstantDataSource< std::vector<KDL::Rotation> >;
template class RTT::internal::ReferenceDataSource< std::vector<KDL::Rotation> >;
template class RTT::base::ChannelElement< std::vector<KDL::Rotation> >;
template class RTT::OutputPort< std::vector<KDL::Rotation> >;
template class RTT::InputPort< std::vector<KDL::Rotation> >;
template class RTT::Property< std::vector<KDL::Rotation> >;
template class RTT::Attribute< std::vector<KDL::Rotation> >;

namespace KDL{
  using namespace std;
  using namespace RTT;

  void loadRotationTypes(){
    RTT::types::Types()->addType( new KDLTypeInfo<Rotation>("KDL.Rotation") );
    RTT::types::Types()->addType( new SequenceTypeInfo<std::vector< Rotation > >("KDL.Rotation[]") );
  };
}  
