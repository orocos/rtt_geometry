#include "kdlTypekit.hpp"

template class RTT::internal::DataSource< ::KDL::Twist >;
template class RTT::internal::AssignableDataSource< ::KDL::Twist >;
template class RTT::internal::ValueDataSource< ::KDL::Twist >;
template class RTT::internal::ConstantDataSource< ::KDL::Twist >;
template class RTT::internal::ReferenceDataSource< ::KDL::Twist >;
template class RTT::base::ChannelElement< ::KDL::Twist >;
template class RTT::OutputPort< ::KDL::Twist >;
template class RTT::InputPort< ::KDL::Twist >;
template class RTT::Property< ::KDL::Twist >;
template class RTT::Attribute< ::KDL::Twist >;
template class RTT::internal::DataSource< std::vector<KDL::Twist> >;
template class RTT::internal::AssignableDataSource< std::vector<KDL::Twist> >;
template class RTT::internal::ValueDataSource< std::vector<KDL::Twist> >;
template class RTT::internal::ConstantDataSource< std::vector<KDL::Twist> >;
template class RTT::internal::ReferenceDataSource< std::vector<KDL::Twist> >;
template class RTT::base::ChannelElement< std::vector<KDL::Twist> >;
template class RTT::OutputPort< std::vector<KDL::Twist> >;
template class RTT::InputPort< std::vector<KDL::Twist> >;
template class RTT::Property< std::vector<KDL::Twist> >;
template class RTT::Attribute< std::vector<KDL::Twist> >;

namespace KDL{
  using namespace std;
  using namespace RTT;

  void loadTwistTypes(){
    RTT::types::Types()->addType( new KDLVectorTypeInfo<Twist,6>("KDL.Twist") );
    RTT::types::Types()->addType( new SequenceTypeInfo<std::vector< Twist > >("KDL.Twist[]") );
    RTT::types::Types()->addType( new CArrayTypeInfo<RTT::types::carray< Twist > >("KDL.cTwist[]") );
  }
}  
