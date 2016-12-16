#include <kdl_typekit/transports/mqueue/kdl_mqueue.hpp>
#include <rtt/transports/mqueue/MQTemplateProtocol.hpp>
#include <rtt/transports/mqueue/MQSerializationProtocol.hpp>
#include <rtt/types/TransportPlugin.hpp>
#include <rtt/types/TypekitPlugin.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>
#include <kdl/frames.hpp>
#include <kdl/jacobian.hpp>
#include <kdl/framevel.hpp>
#include <kdl/jntarray.hpp>
#include <kdl/jntarrayvel.hpp>
#include <Eigen/Dense>

using namespace std;
using namespace RTT::detail;
using namespace RTT;
using namespace RTT::mqueue;
using namespace RTT::types;
using namespace Eigen;

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
                ar & boost::serialization::make_array(g.data(), rows * cols);
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
            ar & boost::serialization::make_array(g.data(), rows * cols);
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

namespace boost{
    namespace serialization{
        template<class Archive> inline void serialize(
            Archive & ar,
            KDL::Rotation& g,
            const unsigned int version)
        {
            ar & make_array(g.data,9);
        }
        template<class Archive> inline void serialize(
            Archive & ar,
            KDL::Vector& g,
            const unsigned int version)
        {
            ar & make_array(g.data,3);
        }
        template<class Archive> inline void serialize(
            Archive & ar,
            KDL::Twist& g,
            const unsigned int version)
        {
            ar & make_array(g.rot.data,3);
            ar & make_array(g.vel.data,3);
        }
        template<class Archive> inline void serialize(
            Archive & ar,
            KDL::Wrench& g,
            const unsigned int version)
        {
            ar & make_array(g.force.data,3);
            ar & make_array(g.torque.data,3);
        }
        template<class Archive> inline void serialize(
            Archive & ar,
            KDL::Frame& g,
            const unsigned int version)
        {
            ar & make_array(g.p.data,3);
            ar & make_array(g.M.data,9);
        }
        template<class Archive> inline void serialize(
            Archive & ar,
            KDL::Jacobian& g,
            const unsigned int version)
        {
            serialize(ar,g.data,version);
        }
        template<class Archive> inline void serialize(
            Archive & ar,
            KDL::JntArray& g,
            const unsigned int version)
        {
            serialize(ar,g.data,version);
        }
        template<class Archive> inline void serialize(
            Archive & ar,
            KDL::JntArrayVel& g,
            const unsigned int version)
        {
            serialize(ar,g.q.data,version);
            serialize(ar,g.qdot.data,version);
        }

    }
}
namespace RTT {
    namespace mqueue {
        bool MQKDLPlugin::registerTransport(std::string name, TypeInfo* ti)
        {
            if ( name == "KDL.Vector" )
                return ti->addProtocol(ORO_MQUEUE_PROTOCOL_ID, new MQSerializationProtocol<KDL::Vector>() );
            if ( name == "KDL.Rotation" )
                return ti->addProtocol(ORO_MQUEUE_PROTOCOL_ID, new MQSerializationProtocol<KDL::Rotation>() );
            if ( name == "KDL.Frame" )
                return ti->addProtocol(ORO_MQUEUE_PROTOCOL_ID, new MQSerializationProtocol<KDL::Frame>() );
            if ( name == "KDL.Wrench" )
                return ti->addProtocol(ORO_MQUEUE_PROTOCOL_ID, new MQSerializationProtocol<KDL::Wrench>() );
            if ( name == "KDL.Twist" )
                return ti->addProtocol(ORO_MQUEUE_PROTOCOL_ID, new MQSerializationProtocol<KDL::Twist>() );
            if ( name == "KDL.Jacobian" )
                return ti->addProtocol(ORO_MQUEUE_PROTOCOL_ID, new MQSerializationProtocol<KDL::Jacobian>() );
            if ( name == "KDL.JntArray" )
                return ti->addProtocol(ORO_MQUEUE_PROTOCOL_ID, new MQSerializationProtocol<KDL::JntArray>() );
            if ( name == "KDL.JntArrayVel" )
                return ti->addProtocol(ORO_MQUEUE_PROTOCOL_ID, new MQSerializationProtocol<KDL::JntArrayVel>() );

            return false;
        }

        std::string MQKDLPlugin::getTransportName() const {
            return "mqueue";
        }

        std::string MQKDLPlugin::getTypekitName() const {
            return "KDL";
        }
        std::string MQKDLPlugin::getName() const {
            return "kdl-mqueue-types";
        }
    }
}

ORO_TYPEKIT_PLUGIN( RTT::mqueue::MQKDLPlugin )

