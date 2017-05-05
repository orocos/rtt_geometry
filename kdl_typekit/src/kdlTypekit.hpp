/******************************************************************************
*                   This file is part of the KDL project                      *
*                                                                             *
*                     (C) 2010 Ruben Smits                                    *
*                         2010 Steven Bellens                                 *
*                     ruben.smits@mech.kuleuven.be                            *
*                     steven.bellens@mech.kuleuven.be                         *
*                    Department of Mechanical Engineering,                    *
*                   Katholieke Universiteit Leuven, Belgium.                  *
*                                                                             *
*       You may redistribute this software and/or modify it under either the  *
*       terms of the GNU Lesser General Public License version 2.1 (LGPLv2.1  *
*       <http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html>) or (at your *
*       discretion) of the Modified BSD License:                              *
*       Redistribution and use in source and binary forms, with or without    *
*       modification, are permitted provided that the following conditions    *
*       are met:                                                              *
*       1. Redistributions of source code must retain the above copyright     *
*       notice, this list of conditions and the following disclaimer.         *
*       2. Redistributions in binary form must reproduce the above copyright  *
*       notice, this list of conditions and the following disclaimer in the   *
*       documentation and/or other materials provided with the distribution.  *
*       3. The name of the author may not be used to endorse or promote       *
*       products derived from this software without specific prior written    *
*       permission.                                                           *
*       THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR  *
*       IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED        *
*       WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE    *
*       ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,*
*       INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES    *
*       (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS       *
*       OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) *
*       HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,   *
*       STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING *
*       IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE    *
*       POSSIBILITY OF SUCH DAMAGE.                                           *
*                                                                             *
*******************************************************************************/
/* @Description:
 * @brief KDL typekit for Orocos RTT
 * @Author: Ruben Smits, Steven Bellens
 */

#ifndef ORO_KDL_TYPEKIT_HPP
#define ORO_KDL_TYPEKIT_HPP

#include <kdl_typekit/typekit/Types.hpp>
#include <rtt/types/TypekitPlugin.hpp>
#include <kdl/frames.hpp>
#include <rtt/types/Types.hpp>
#include <rtt/types/TemplateTypeInfo.hpp>
#include <rtt/types/SequenceTypeInfo.hpp>
#include <rtt/types/StructTypeInfo.hpp>
#include <rtt/types/carray.hpp>
#include <rtt/types/CArrayTypeInfo.hpp>
#include <rtt/types/Operators.hpp>
#include <rtt/types/OperatorTypes.hpp>
#include <rtt/internal/mystd.hpp>
#include <rtt/os/StartStopManager.hpp>
#include <rtt/internal/GlobalService.hpp>

#include <kdl/frames_io.hpp>

#include <kdl/jntarray.hpp>
#include <kdl/jacobian.hpp>

#include "motionproperties.hpp"
#include "kinfamproperties.hpp"

namespace KDL
{
  using namespace RTT;
  using namespace RTT::detail;
  using namespace std;

  /**
   * Helper functions.
   */
  /**
   * Returns a reference to one item in an KDL container.
   * @param cont The container to access
   * @param index The item to reference
   * @return A reference to item \a index
   */
  template<class KDLType, int size>
  double& get_container_item(KDLType & cont, int index)
  {
      if (index >= size || index < 0)
          return internal::NA<double&>::na();
      return cont[index];
  }

  /**
   * Returns a copy to one item in an STL container.
   * @note vector<bool> is not supported, since it's not an STL container.
   * @param cont The container to access
   * @param index The item to extract from the sequence
   * @return A copy of item \a index
   */
  template<class KDLType, int size>
  double get_container_item_copy(const KDLType & cont, int index)
  {
      if (index >= size || index < 0)
          return internal::NA<double>::na();
      return cont[index];
  }

  /**
   * KDL RTT bindings
   */
  class KDLTypekitPlugin
    : public RTT::types::TypekitPlugin
  {
  public:
    virtual std::string getName();

    virtual bool loadTypes();
    virtual bool loadConstructors();
    virtual bool loadOperators();
  };

  /**
   * Temlate class used for Vector, Twist and Wrench
   */
  template<class KDLType, int size>
  struct KDLVectorTypeInfo
    : public StructTypeInfo<KDLType,true>
  {
      KDLVectorTypeInfo(std::string name) : StructTypeInfo<KDLType,true>(name) {}
    
    virtual bool decomposeTypeImpl(const KDLType& source, PropertyBag& targetbag ) const {
      decomposeProperty( source, targetbag );
      return true;
    }
    
    virtual bool composeTypeImpl(const PropertyBag& source, KDLType& result) const {
      return composeProperty( source, result );
    }

    base::DataSourceBase::shared_ptr getMember(base::DataSourceBase::shared_ptr item,
            base::DataSourceBase::shared_ptr id) const {
        // discover if user gave us a part name or index:
        typename internal::DataSource<int>::shared_ptr id_indx = internal::DataSource<int>::narrow( internal::DataSourceTypeInfo<int>::getTypeInfo()->convert(id).get() );
        if ( id_indx ) {
            try {
                if ( item->isAssignable() )
                    return internal::newFunctorDataSource(&get_container_item<KDLType,size>, internal::GenerateDataSource()(item.get(), id_indx.get() ) );
                else
                    return internal::newFunctorDataSource(&get_container_item_copy<KDLType,size>, internal::GenerateDataSource()(item.get(), id_indx.get() ) );
            } catch(...) {}
        }
        if (id_indx) {
            log(Error) << "KDLVectorTypeInfo: Invalid index : " << id_indx->get() <<":"<< id_indx->getTypeName() << endlog();
        }
        if ( ! id_indx)
            log(Error) << "KDLVectorTypeInfo: Not a member or index : " << id <<":"<< id->getTypeName() << endlog();
        return base::DataSourceBase::shared_ptr();
    }
  };

  /**
   * Template class used for Frame, Rotation
   */
  template<class KDLType>
  struct KDLTypeInfo
    : public StructTypeInfo<KDLType,true>
  {
    KDLTypeInfo(std::string name) : StructTypeInfo<KDLType,true>(name) {}

    virtual bool decomposeTypeImpl(const KDLType& source, PropertyBag& targetbag ) const {
      decomposeProperty( source, targetbag );
      return true;
    }

    virtual bool composeTypeImpl(const PropertyBag& source, KDLType& result) const {
      return composeProperty( source, result );
    }

  };

  /**
   * The single global instance of the KDL Typekit.
   */
  extern KDLTypekitPlugin KDLTypekit;
}
#endif
