#include <Eigen/Dense>
#include <EigenTypesC.h>

namespace RTT
{
  namespace corba{

    template<>
    struct AnyConversion< Eigen::VectorXd >
    {
        //typedef CORBA::DoubleSeq CorbaType;
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
          //log(Debug)<< "Size of Vector is NULL"<< endlog();
          return true;
        }
                AnyConversion<double>::toCorbaType(cb,1.);
        //log(Debug)<< "Converting type 'Eigen::VectorXd' (size "<<tp.size()<<") to sequence<CORBA::Double> (size "<< cb.length()<<")"<<endlog();
        cb.length( (CORBA::ULong)(tp.size()) );
        Eigen::Map<Eigen::VectorXd>(cb.get_buffer(/*CORBA::Boolean(false)*/) , cb.length()) = tp;
        //log(Debug)<< "DONE Converting type 'Eigen::VectorXd' (size "<<tp.size()<<") to sequence<CORBA::Double> (size "<< cb.length()<<")"<<endlog();
        return true;
      }
    
      static bool toStdType(StdType& tp, const CorbaType& cb){
        if(!cb.length()){
          //log(Debug)<< "Size of CORBA is NULL"<< endlog();
          return false;
        }
	      //log(Debug)<< "Converting type sequence<CORBA::Double> (size "<< cb.length()<<") to 'Eigen::VectorXd' (size "<<tp.size()<<")" <<endlog();
        tp.resize( cb.length() );
        tp = Eigen::VectorXd::Map(cb.get_buffer() , cb.length());
        //log(Debug)<< "DONE Converting type sequence<CORBA::Double> (size "<< cb.length()<<") to 'Eigen::VectorXd' (size "<<tp.size()<<")" <<endlog();
	      return true;
      }

    };
    
    template<>
    struct AnyConversion< Eigen::MatrixXd >
    {
      //typedef CORBA::DoubleSeq CorbaType;
      typedef Eigen::corba::DoubleSequence CorbaType;
      typedef Eigen::MatrixXd StdType;

      static CorbaType* toAny(const StdType& tp) {
        //log(Debug)<< "'Eigen::MatrixXd' toAny" <<endlog();
        CorbaType* cb = new CorbaType();
        toCorbaType(*cb, tp);
        return cb;
      }

      static bool update(const CORBA::Any& any, StdType& _value) {
        //log(Debug)<< "'Eigen::MatrixXd' update(const CORBA::Any& any, StdType& _value)" <<endlog();
        CorbaType* result;
        if ( any >>= result ) {
          return toStdType(_value, *result);
        }
        return false;
      }

      static CORBA::Any_ptr createAny( const StdType& t ) {
        //log(Debug)<< "'Eigen::MatrixXd' createAny( const StdType& t ) " <<endlog();
        CORBA::Any_ptr ret = new CORBA::Any();
        *ret <<= toAny( t );
        return ret;
      }

      static bool updateAny( StdType const& t, CORBA::Any& any ) {
        //log(Debug)<< "'Eigen::MatrixXd' updateAny( StdType const& t, CORBA::Any& any )" <<endlog();
        any <<= toAny( t );
        return true;
      }

      static bool toCorbaType(CorbaType& cb, const StdType& tp){
        //log(Debug)<< "Converting type 'Eigen::MatrixXd' (size " << tp.rows()<<"x"<<tp.cols()<<") to sequence<CORBA::Double> "<<cb.length() <<endlog();
        if(!tp.size()){
          //log(Debug)<< "Size of Vector is NULL"<< endlog();
          return false;
        }
        
        
        size_t rows = static_cast<size_t>(tp.rows());
        size_t cols = static_cast<size_t>(tp.cols());

        //if(cols == 0) cols = 1; // For Vectors

        cb.length( (CORBA::ULong)(tp.size() + 2) );
        //log(Debug)<< "Total size for vector out  "<<cb.length() <<endlog();

        cb[0] = static_cast<double>(rows);
        cb[1] = static_cast<double>(cols);
        //log(Debug)<< tp <<endlog();
        Eigen::Map<Eigen::MatrixXd>(cb.get_buffer(/*CORBA::Boolean(false)*/) + 2 , rows, cols) = tp;
        for(int i=0;i<cb.length();i++)
          //log(Debug) << cb[i] <<" ";
        //log(Debug) <<endlog();
        return true;
      }

      static bool toStdType(StdType& tp, const CorbaType& cb){
        //log(Debug)<< "Converting type sequence<CORBA::Double> (size "<<cb.length()<<") to 'Eigen::MatrixXd' (size " << tp.rows()<<"x"<<tp.cols()<<")" <<endlog();
        if(!cb.length() || cb.length() < 2){
          //log(Debug)<< "Size of CORBA is BAD : "<<cb.length()  << endlog();
          return false;
        }
        

        size_t rows = static_cast<size_t>(cb[0]);
        size_t cols = static_cast<size_t>(cb[1]);

        //if(cols == 0) cols = 1; // For Vectors

        //log(Debug)<< "rows,cols : "<<rows<<" "          <<cols <<endlog();
        tp.resize(rows,cols);

        tp = Eigen::MatrixXd::Map(cb.get_buffer()+2,rows,cols);
        //log(Debug)<<"Final out : \n"<< tp <<endlog();
        return true;
      }

    };
    
  };//namespace corba
};//namespace RTT

