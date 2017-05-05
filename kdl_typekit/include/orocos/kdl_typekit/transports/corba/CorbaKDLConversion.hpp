#ifndef ORO_KDL_CORBAKDLCONVERSION_HPP
#define ORO_KDL_CORBAKDLCONVERSION_HPP 1

#include <kdl_typekit/transports/corba/KDLTypesC.h>
#include <rtt/transports/corba/CorbaConversion.hpp>
#include <kdl/frames.hpp>
#include <kdl/jacobian.hpp>
#include <kdl/jntarray.hpp>
#include <Eigen/Dense>

namespace RTT
{
  namespace corba{

    template<>
    struct AnyConversion< KDL::Vector >
    {
        typedef KDL::Corba::DoubleSequence CorbaType;
        typedef KDL::Vector StdType;
        static CorbaType toAny(const KDL::Vector& orig) {
            log(Debug)<< "Converting type 'KDL::Vector' to sequence<CORBA::Double>." <<endlog();
            CorbaType ret;
            ret.length( 3 );
	    ret[0] = orig.x();
	    ret[1] = orig.y();
	    ret[2] = orig.z();
            return ret;
        }
      
        static bool updateAny( StdType const& t, CORBA::Any& any ) {
            any <<= toAny( t );
            return true;
        }

      
        static bool update(const CORBA::Any& any, StdType& _value) {
            log(Debug)<< "update KDL::Vector" <<endlog();
            CorbaType* result;
            if ( any >>=  result )  {
	        return toStdType(_value,*result);
            }
            return false;
        }

        static CORBA::Any_ptr createAny( const StdType& t ) {
            CORBA::Any_ptr ret = new CORBA::Any();
            *ret <<= toAny( t );
            return ret;
        }

      static bool toCorbaType(CorbaType& cb, const StdType& tp){
	cb = toAny(tp);
	return true;
      }

      static bool toStdType(StdType& tp, const CorbaType& cb){
	log(Debug)<< "Converting type sequence<CORBA::Double> to 'KDL::Vector'" <<endlog();
	tp.x(cb[0]);
	tp.y(cb[1]);
	tp.z(cb[2]);
	return true;
      }

    };

    template<>
    struct AnyConversion< KDL::Rotation >
    {
        typedef KDL::Corba::DoubleSequence CorbaType;
        typedef KDL::Rotation StdType;
        static CorbaType toAny(const KDL::Rotation& orig) {
            log(Debug)<< "Converting type 'KDL::Rotation' to sequence<CORBA::Double>." <<endlog();
            CorbaType ret;
            ret.length( 9 );
	    ret[0] = orig(0,0);
	    ret[1] = orig(0,1);
	    ret[2] = orig(0,2);
	    ret[3] = orig(1,0);
	    ret[4] = orig(1,1);
	    ret[5] = orig(1,2);
	    ret[6] = orig(2,0);
	    ret[7] = orig(2,1);
	    ret[8] = orig(2,2);
            return ret;
        }

      static bool toStdType(StdType& tp ,const CorbaType& cb) {
            log(Debug)<< "Converting type sequence<CORBA::Double> to 'KDL::Rotation'" <<endlog();
	    tp = StdType(cb[0],cb[1],cb[2],cb[3],cb[4],cb[5],cb[6],cb[7],cb[8]);
            return true;
        }

      static bool toCorbaType(CorbaType& cb, const StdType& tp){
	cb = toAny(tp);
	return true;
      }

        static bool update(const CORBA::Any& any, StdType& _value) {
            log(Debug)<< "update KDL::Rotation" <<endlog();
            CorbaType* result;
            if ( any >>=  result )  {
	        return toStdType(_value,*result);
            }
            return false;
        }

        static CORBA::Any_ptr createAny( const KDL::Rotation& t ) {
            CORBA::Any_ptr ret = new CORBA::Any();
            *ret <<= toAny( t );
            return ret;
        }

        static bool updateAny( StdType const& t, CORBA::Any& any ) {
            any <<= toAny( t );
            return true;
        }

    };

    template<>
    struct AnyConversion< KDL::Frame >
    {
        typedef KDL::Corba::DoubleSequence CorbaType;
        typedef KDL::Frame StdType;
        static CorbaType toAny(const KDL::Frame& orig) {
            log(Debug)<< "Converting type 'KDL::Frame' to sequence<CORBA::Double>." <<endlog();
            CorbaType ret;
            ret.length( 12 );
	    ret[0] = orig.p.x();
	    ret[1] = orig.p.y();
	    ret[2] = orig.p.z();
	    ret[3] = orig.M(0,0);
	    ret[4] = orig.M(0,1);
	    ret[5] = orig.M(0,2);
	    ret[6] = orig.M(1,0);
	    ret[7] = orig.M(1,1);
	    ret[8] = orig.M(1,2);
	    ret[9] = orig.M(2,0);
	    ret[10] = orig.M(2,1);
	    ret[11] = orig.M(2,2);
            return ret;
        }

        static bool updateAny( StdType const& t, CORBA::Any& any ) {
            any <<= toAny( t );
            return true;
        }
        static bool update(const CORBA::Any& any, StdType& _value) {
            log(Debug)<< "update KDL::Frame" <<endlog();
            CorbaType* result;
            if ( any >>=  result )  {
	        return toStdType(_value,*result);
            }
            return false;
        }

        static CORBA::Any_ptr createAny( const StdType& t ) {
            CORBA::Any_ptr ret = new CORBA::Any();
            *ret <<= toAny( t );
            return ret;
        }

        static bool toStdType(StdType& tp, const CorbaType& cb) {
            log(Debug)<< "Converting type sequence<CORBA::Double> to 'KDL::Frame'" <<endlog();
	    tp.p.x(cb[0]);
	    tp.p.y(cb[1]);
	    tp.p.z(cb[2]);
	    tp.M(0,0)=cb[3];
	    tp.M(0,1)=cb[4];
	    tp.M(0,2)=cb[5];
	    tp.M(1,0)=cb[6];
	    tp.M(1,1)=cb[7];
	    tp.M(1,2)=cb[8];
	    tp.M(2,0)=cb[9];
	    tp.M(2,1)=cb[10];
	    tp.M(2,2)=cb[11];
            return true;
        }

      static bool toCorbaType(CorbaType& cb, const StdType& tp){
	cb = toAny(tp);
	return true;
      }

    };

    template<>
    struct AnyConversion< KDL::Wrench >
    {
        typedef KDL::Corba::DoubleSequence CorbaType;
        typedef KDL::Wrench StdType;
        static CorbaType toAny(const KDL::Wrench& orig) {
            log(Debug)<< "Converting type 'KDL::Wrench' to sequence<CORBA::Double>." <<endlog();
            CorbaType ret;
            ret.length( 6 );
	    ret[0] = orig.force.x();
	    ret[1] = orig.force.y();
	    ret[2] = orig.force.z();
	    ret[3] = orig.torque.x();
	    ret[4] = orig.torque.y();
	    ret[5] = orig.torque.z();
            return ret;
        }

        static bool updateAny( StdType const& t, CORBA::Any& any ) {
            any <<= toAny( t );
            return true;
        }

      
        static bool update(const CORBA::Any& any, StdType& _value) {
            log(Debug)<< "update KDL::Vector" <<endlog();
            CorbaType* result;
            if ( any >>=  result )  {
	        return toStdType(_value,*result);
            }
            return false;
        }

        static CORBA::Any_ptr createAny( const StdType& t ) {
            CORBA::Any_ptr ret = new CORBA::Any();
            *ret <<= toAny( t );
            return ret;
        }

      static bool toStdType(StdType& tp, const CorbaType& cb){
            log(Debug)<< "Converting type sequence<CORBA::Double> to 'KDL::Wrench'" <<endlog();
	    tp.force.x(cb[0]);
	    tp.force.y(cb[1]);
	    tp.force.z(cb[2]);
	    tp.torque.x(cb[3]);
	    tp.torque.y(cb[4]);
	    tp.torque.z(cb[5]);
            return true;
        }
      static bool toCorbaType(CorbaType& cb, const StdType& tp){
	cb = toAny(tp);
	return true;
      }

    };

    template<>
    struct AnyConversion< KDL::Twist >
    {
        typedef KDL::Corba::DoubleSequence CorbaType;
        typedef KDL::Twist StdType;
        static CorbaType toAny(const KDL::Twist& orig) {
            log(Debug)<< "Converting type 'KDL::Twist' to sequence<CORBA::Double>." <<endlog();
            CorbaType ret;
            ret.length( 6 );
	    ret[0] = orig.vel.x();
	    ret[1] = orig.vel.y();
	    ret[2] = orig.vel.z();
	    ret[3] = orig.rot.x();
	    ret[4] = orig.rot.y();
	    ret[5] = orig.rot.z();
            return ret;
        }

        static bool updateAny( StdType const& t, CORBA::Any& any ) {
            any <<= toAny( t );
            return true;
        }

      
        static bool update(const CORBA::Any& any, StdType& _value) {
            log(Debug)<< "update KDL::Vector" <<endlog();
            CorbaType* result;
            if ( any >>=  result )  {
	        return toStdType(_value,*result);
            }
            return false;
        }

        static CORBA::Any_ptr createAny( const StdType& t ) {
            CORBA::Any_ptr ret = new CORBA::Any();
            *ret <<= toAny( t );
            return ret;
        }

      static bool toCorbaType(CorbaType& cb, const StdType& tp){
	cb = toAny(tp);
	return true;
      }

      static bool toStdType(StdType& tp, const CorbaType& cb){
            log(Debug)<< "Converting type sequence<CORBA::Double> to 'KDL::Twist'" <<endlog();
	    tp.vel.x(cb[0]);
	    tp.vel.y(cb[1]);
	    tp.vel.z(cb[2]);
	    tp.rot.x(cb[3]);
	    tp.rot.y(cb[4]);
	    tp.rot.z(cb[5]);
            return true;
        }
    };
    template<>
    struct AnyConversion< KDL::Jacobian >
    {
        typedef KDL::Corba::DoubleSequence CorbaType;
        typedef KDL::Jacobian StdType;
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
        
        size_t rows = static_cast<size_t>(tp.data.rows());
        size_t cols = static_cast<size_t>(tp.data.cols());

        cb.length( (CORBA::ULong)(tp.data.size() + 2) );

        cb[0] = static_cast<double>(rows);
        cb[1] = static_cast<double>(cols);
        
        Eigen::Map<Eigen::MatrixXd>(cb.get_buffer() + 2 , rows, cols) = tp.data;

        return true;
      }

      static bool toStdType(StdType& tp, const CorbaType& cb){
        if(cb.length() < 2){
          return false;
        }

        size_t rows = static_cast<size_t>(cb[0]);
        size_t cols = static_cast<size_t>(cb[1]);

        tp.resize(cols);

        tp.data = Eigen::MatrixXd::Map(cb.get_buffer()+2,rows,cols);
        return true;
      }

    };

    template<>
    struct AnyConversion< KDL::JntArray >
    {
        typedef KDL::Corba::DoubleSequence CorbaType;
        typedef KDL::JntArray StdType;

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
        cb.length( (CORBA::ULong)(tp.rows() ));
        Eigen::Map<Eigen::VectorXd>(cb.get_buffer() , cb.length()) = tp.data;
        return true;
      }
    
      static bool toStdType(StdType& tp, const CorbaType& cb){
        tp.resize( cb.length() );
        tp.data = Eigen::VectorXd::Map(cb.get_buffer() , cb.length());
        return true;
      }
    };
  } //namespace corba
} //namespace RTT

#endif // ORO_KDL_CORBAKDLCONVERSION_HPP
