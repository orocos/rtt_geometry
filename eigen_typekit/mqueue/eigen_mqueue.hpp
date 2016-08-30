#ifndef __EIGEN_MQUEUE_PLUGIN__
#define __EIGEN_MQUEUE_PLUGIN__

#include <rtt/types/TransportPlugin.hpp>

namespace RTT
{
    namespace mqueue
    {
        /** The MQueue transport plugin */
        struct MQEigenPlugin: public RTT::types::TransportPlugin
        {
            bool registerTransport(std::string name, RTT::types::TypeInfo* ti);
            std::string getTransportName() const;
            std::string getTypekitName() const;
            std::string getName() const;
        };
    }
}


#endif

