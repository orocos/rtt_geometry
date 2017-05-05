// Copyright  (C)  2008  Ruben Smits <ruben dot smits at mech dot kuleuven dot be>

// Version: 1.0
// Author: Ruben Smits <ruben dot smits at mech dot kuleuven dot be>
// Maintainer: Ruben Smits <ruben dot smits at mech dot kuleuven dot be>
// URL: http://www.orocos.org/kdl

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include <eigen_typekit/transports/corba/corbatoolkit.hpp>
#include <rtt/types/Types.hpp>
#include <rtt/transports/corba/CorbaTemplateProtocol.hpp>
#include <eigen_typekit/transports/corba/CorbaEigenConversion.hpp>
#include <rtt/types/TypekitPlugin.hpp>

using namespace RTT;
using namespace RTT::types;
using namespace RTT::corba;

namespace Eigen
{
    namespace corba
    {

            bool CorbaEigenPlugin::registerTransport(std::string name, TypeInfo* ti)
            {
                if ( name == "eigen_vector" )
                    return ti->addProtocol(ORO_CORBA_PROTOCOL_ID, new CorbaTemplateProtocol< Eigen::VectorXd >() );
                if ( name == "eigen_matrix" )
                    return ti->addProtocol(ORO_CORBA_PROTOCOL_ID, new CorbaTemplateProtocol< Eigen::MatrixXd >() );
                return false;
            }

            std::string CorbaEigenPlugin::getTransportName() const {
                return "CORBA";
            }
            std::string CorbaEigenPlugin::getTypekitName() const {
                return "Eigen";
            }

            std::string CorbaEigenPlugin::getName() const {
                return "eigen-corba-types";
            }
    }
}

ORO_TYPEKIT_PLUGIN( Eigen::corba::CorbaEigenPlugin)

