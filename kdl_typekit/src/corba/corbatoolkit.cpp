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

#include <kdl_typekit/transports/corba/corbatoolkit.hpp>
#include <rtt/types/Types.hpp>
#include <rtt/transports/corba/CorbaTemplateProtocol.hpp>
#include <kdl_typekit/transports/corba/CorbaKDLConversion.hpp>
#include <rtt/types/TypekitPlugin.hpp>

using namespace RTT;
using namespace RTT::types;
using namespace RTT::corba;

namespace KDL
{
    namespace Corba
    {

            bool CorbaKDLPlugin::registerTransport(std::string name, TypeInfo* ti)
            {
                if ( name == "KDL.Vector" )
                    return ti->addProtocol(ORO_CORBA_PROTOCOL_ID, new CorbaTemplateProtocol< KDL::Vector >() );
                if ( name == "KDL.Rotation" )
                    return ti->addProtocol(ORO_CORBA_PROTOCOL_ID, new CorbaTemplateProtocol< KDL::Rotation >() );
                if ( name == "KDL.Frame" )
                    return ti->addProtocol(ORO_CORBA_PROTOCOL_ID, new CorbaTemplateProtocol< KDL::Frame >() );
                if ( name == "KDL.Wrench" )
                    return ti->addProtocol(ORO_CORBA_PROTOCOL_ID, new CorbaTemplateProtocol< KDL::Wrench >() );
                if ( name == "KDL.Twist" )
                    return ti->addProtocol(ORO_CORBA_PROTOCOL_ID, new CorbaTemplateProtocol< KDL::Twist >() );
                if ( name == "KDL.Jacobian" )
                    return ti->addProtocol(ORO_CORBA_PROTOCOL_ID, new CorbaTemplateProtocol< KDL::Jacobian >() );
                if ( name == "KDL.JntArray" )
                    return ti->addProtocol(ORO_CORBA_PROTOCOL_ID, new CorbaTemplateProtocol< KDL::JntArray >() );
                return false;
            }

            std::string CorbaKDLPlugin::getTransportName() const {
                return "CORBA";
            }
            std::string CorbaKDLPlugin::getTypekitName() const {
                return "KDL";
            }

            std::string CorbaKDLPlugin::getName() const {
                return "kdl-corba-types";
            }
    }
}

ORO_TYPEKIT_PLUGIN( KDL::Corba::CorbaKDLPlugin)

