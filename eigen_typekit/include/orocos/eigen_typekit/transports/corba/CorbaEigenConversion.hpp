#ifndef ORO_EIGEN_CORBAEIGENCONVERSION_HPP
#define ORO_EIGEN_CORBAEIGENCONVERSION_HPP 1

#include <Eigen/Dense>
#include <eigen_typekit/transports/corba/EigenTypesC.h>

namespace RTT
{
  namespace corba{

    template<>
    struct AnyConversion< Eigen::VectorXd >
    {
        typedef Eigen::corba::DoubleSequence CorbaType;
        typedef Eigen::VectorXd StdType;

      static CorbaType* toAny(const StdType& tp) {
        CorbaType* cb = new CorbaType();
        toCorbaType(*cb, tp);
        return cb;
      }

      static bool update(const CORBA::Any& any, StdType& _value) {
        CorbaType* result;
        if ( any >>= result ) {
          return toStdType(_value, *result);
        }
        return false;
      }

      static CORBA::Any_ptr createAny( const StdType& t ) {
        CORBA::Any_ptr ret = new CORBA::Any();
        *ret <<= toAny( t );
        return ret;
      }

      static bool updateAny( StdType const& t, CORBA::Any& any ) {
        any <<= toAny( t );
        return true;
      }

      static bool toCorbaType(CorbaType& cb, const StdType& tp){
        if(!tp.size()){
          return true;
        }
        cb.length( (CORBA::ULong)(tp.size()) );
        Eigen::Map<Eigen::VectorXd>(cb.get_buffer() , cb.length()) = tp;
        return true;
      }

      static bool toStdType(StdType& tp, const CorbaType& cb){
        if(!cb.length()){
          return false;
        }
        tp.resize( cb.length() );
        tp = Eigen::VectorXd::Map(cb.get_buffer() , cb.length());
	      return true;
      }

    };

    template<>
    struct AnyConversion< Eigen::MatrixXd >
    {
      typedef Eigen::corba::DoubleSequence CorbaType;
      typedef Eigen::MatrixXd StdType;

      static CorbaType* toAny(const StdType& tp) {
        CorbaType* cb = new CorbaType();
        toCorbaType(*cb, tp);
        return cb;
      }

      static bool update(const CORBA::Any& any, StdType& _value) {
        CorbaType* result;
        if ( any >>= result ) {
          return toStdType(_value, *result);
        }
        return false;
      }

      static CORBA::Any_ptr createAny( const StdType& t ) {
        CORBA::Any_ptr ret = new CORBA::Any();
        *ret <<= toAny( t );
        return ret;
      }

      static bool updateAny( StdType const& t, CORBA::Any& any ) {
        any <<= toAny( t );
        return true;
      }

      static bool toCorbaType(CorbaType& cb, const StdType& tp){
        if(!tp.size()){
          return false;
        }

        size_t rows = static_cast<size_t>(tp.rows());
        size_t cols = static_cast<size_t>(tp.cols());

        cb.length( (CORBA::ULong)(tp.size() + 2) );

        cb[0] = static_cast<double>(rows);
        cb[1] = static_cast<double>(cols);

        Eigen::Map<Eigen::MatrixXd>(cb.get_buffer() + 2 , rows, cols) = tp;

        return true;
      }

      static bool toStdType(StdType& tp, const CorbaType& cb){
        if(!cb.length() || cb.length() < 2){
          return false;
        }

        size_t rows = static_cast<size_t>(cb[0]);
        size_t cols = static_cast<size_t>(cb[1]);

        tp.resize(rows,cols);

        tp = Eigen::MatrixXd::Map(cb.get_buffer()+2,rows,cols);

        return true;
      }

    };

  } //namespace corba
} //namespace RTT

#endif // ORO_EIGEN_CORBAEIGENCONVERSION_HPP
