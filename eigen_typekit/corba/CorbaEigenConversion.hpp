#include <rtt/transports/corba/RTTCorbaConversion.hpp>
#include <Eigen/Dense>

namespace RTT
{
  namespace corba{

    template<>
    struct AnyConversion< Eigen::VectorXd >
    {
        typedef typename AnyConversion<double>::sequence CorbaType;
        typedef Eigen::VectorXd StdType;
      
      /**
      * if T is a std::vector or a std::map the associated type is CORBA::Any
      */
      static bool toStdType(StdType& tp, const CORBA::Any& any) {
        return update(any, tp);
      }
      static bool toCorbaType(CORBA::Any& any, const StdType& tp) {
        return updateAny(tp, any);
      }

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
        log(Debug)<< "Converting type 'Eigen::VectorXd' to sequence<CORBA::Double>" <<endlog();
        bool res = true;
        cb.length( (CORBA::ULong)(tp.size()) );
        for( size_t i = 0; i != tp.size(); ++i){
          res &= AnyConversion<double>::toCorbaType(cb[(CORBA::ULong)(i)], tp[i]);
        }
        return res;
      }
    
      static bool toStdType(StdType& tp, const CorbaType& cb){
	log(Debug)<< "Converting type sequence<CORBA::Double> to 'Eigen::VectorXd'" <<endlog();
        bool res=true;
        tp.resize( cb.length() );
        for (size_t i = 0; i != cb.length(); ++i) {
          res &= AnyConversion<double>::toStdType(tp[i], cb[(CORBA::ULong)(i)]);
        }
	return true;
      }

    };
    
    template<>
    struct AnyConversion< Eigen::MatrixXd >
    {
        typedef typename AnyConversion<double>::sequence CorbaType;
        typedef Eigen::MatrixXd StdType;
      
      /**
      * if T is a std::vector or a std::map the associated type is CORBA::Any
      */
      static bool toStdType(StdType& tp, const CORBA::Any& any) {
        return update(any, tp);
      }
      static bool toCorbaType(CORBA::Any& any, const StdType& tp) {
        return updateAny(tp, any);
      }

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
        bool res = true;
        cb.length( (CORBA::ULong)(tp.rows() * tp.cols()) + 2);
        log(Debug)<< "Taille  "<<tp.rows() * tp.cols() + 2 <<endlog();
        res &= AnyConversion<double>::toCorbaType(cb[(CORBA::ULong)(0)] ,(double)(tp.rows()));
        res &= AnyConversion<double>::toCorbaType(cb[(CORBA::ULong)(1)] , (double)(tp.cols()));
        for( size_t i = 0; i != tp.rows(); ++i)
            for( size_t j = 0; j != tp.cols(); ++j)
                res &= AnyConversion<double>::toCorbaType(cb[(CORBA::ULong)(i*tp.rows() + j + 2)], tp(i,j));
        return res;
      }

      static bool toStdType(StdType& tp, const CorbaType& cb){
        log(Debug)<< "Converting type sequence<CORBA::Double> to 'Eigen::MatrixXd'" <<endlog();
        bool res=true;
        double rows_(0),cols_(0);
        double& rows = rows_;
        double& cols = cols_;
        res &= AnyConversion<double>::toStdType(rows, cb[(CORBA::ULong)(0)]);
        res &= AnyConversion<double>::toStdType(cols, cb[(CORBA::ULong)(1)]);
        log(Debug)<< "rows,cols : "<<rows<<" "          <<cols <<endlog();
        tp.resize(rows,cols);
        for (size_t i = 0; i != (int)(rows); ++i)
            for( size_t j = 0; j != (int)(cols); ++j)
                res = res && AnyConversion<double>::toStdType(tp(i,j), cb[(CORBA::ULong)(2 + i*rows + j)]);
        
        return true;
      }

    };
    
  };//namespace corba
};//namespace RTT

