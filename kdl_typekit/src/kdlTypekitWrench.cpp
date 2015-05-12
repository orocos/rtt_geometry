#include "kdlTypekit.hpp"

namespace KDL{
  using namespace std;
  using namespace RTT;

  void loadWrenchTypes(){
    RTT::types::Types()->addType( new KDLVectorTypeInfo<Wrench,6>("KDL.Wrench") );
    RTT::types::Types()->addType( new SequenceTypeInfo<std::vector< Wrench > >("KDL.Wrench[]") );
  };
}  
