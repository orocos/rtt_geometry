#include <eigen_typekit/transports/mqueue/eigen_mqueue.hpp>
#include <rtt/transports/mqueue/MQTemplateProtocol.hpp>
#include <rtt/transports/mqueue/MQSerializationProtocol.hpp>
#include <rtt/types/TransportPlugin.hpp>
#include <rtt/types/TypekitPlugin.hpp>
#include <boost/serialization/vector.hpp>
#include <Eigen/Dense>

using namespace std;
using namespace RTT::detail;
using namespace Eigen;
using namespace RTT;
using namespace RTT::mqueue;
using namespace RTT::types;
  
// From Shmuel Levine : http://stackoverflow.com/questions/18382457/eigen-and-boostserialize
namespace boost{
    namespace serialization{

        template<   class Archive, 
                    class S, 
                    int Rows_, 
                    int Cols_, 
                    int Ops_, 
                    int MaxRows_, 
                    int MaxCols_>
        inline void save(
            Archive & ar, 
            const Eigen::Matrix<S, Rows_, Cols_, Ops_, MaxRows_, MaxCols_> & g, 
            const unsigned int version)
            {
                int rows = g.rows();
                int cols = g.cols();

                ar & rows;
                ar & cols;
                ar & boost::serialization::make_array(g.data(), g.size());
            }

        template<   class Archive, 
                    class S, 
                    int Rows_,
                    int Cols_,
                    int Ops_, 
                    int MaxRows_, 
                    int MaxCols_>
        inline void load(
            Archive & ar, 
            Eigen::Matrix<S, Rows_, Cols_, Ops_, MaxRows_, MaxCols_> & g, 
            const unsigned int version)
        {
            int rows, cols;
            ar & rows;
            ar & cols;
            g.resize(rows, cols);
            ar & boost::serialization::make_array(g.data(), g.size());
        }

        template<   class Archive, 
                    class S, 
                    int Rows_, 
                    int Cols_, 
                    int Ops_, 
                    int MaxRows_, 
                    int MaxCols_>
        inline void serialize(
            Archive & ar, 
            Eigen::Matrix<S, Rows_, Cols_, Ops_, MaxRows_, MaxCols_> & g, 
            const unsigned int version)
        {
            split_free(ar, g, version);
        }


    } // namespace serialization
} // namespace boost
namespace RTT {
    namespace mqueue {
        bool MQEigenPlugin::registerTransport(std::string name, TypeInfo* ti)
        {
            if ( name == "eigen_vector" )
                return ti->addProtocol(ORO_MQUEUE_PROTOCOL_ID, new MQSerializationProtocol<Eigen::VectorXd>() );
            if ( name == "eigen_matrix" )
                return ti->addProtocol(ORO_MQUEUE_PROTOCOL_ID, new MQSerializationProtocol<Eigen::MatrixXd>() );

            return false;
        }

        std::string MQEigenPlugin::getTransportName() const {
            return "mqueue";
        }

        std::string MQEigenPlugin::getTypekitName() const {
            return "Eigen";
        }
        std::string MQEigenPlugin::getName() const {
            return "eigen-mqueue-types";
        }
    }
}

ORO_TYPEKIT_PLUGIN( RTT::mqueue::MQEigenPlugin )

