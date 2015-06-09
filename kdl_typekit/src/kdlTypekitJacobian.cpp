#include "kdlTypekit.hpp"

template class RTT::internal::DataSource< ::KDL::Jacobian >;
template class RTT::internal::AssignableDataSource< ::KDL::Jacobian >;
template class RTT::internal::ValueDataSource< ::KDL::Jacobian >;
template class RTT::internal::ConstantDataSource< ::KDL::Jacobian >;
template class RTT::internal::ReferenceDataSource< ::KDL::Jacobian >;
template class RTT::base::ChannelElement< ::KDL::Jacobian >;
template class RTT::OutputPort< ::KDL::Jacobian >;
template class RTT::InputPort< ::KDL::Jacobian >;
template class RTT::Property< ::KDL::Jacobian >;
template class RTT::Attribute< ::KDL::Jacobian >;

namespace KDL{
  using namespace std;
  using namespace RTT;

  void loadJacobianTypes(){
    RTT::types::Types()->addType( new KDLTypeInfo<Jacobian>("KDL.Jacobian") );
    RTT::types::Types()->addType( new SequenceTypeInfo<std::vector< Jacobian > >("KDL.Jacobian[]") );
  };

}  
