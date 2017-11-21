// Copyright  (C)  2008  Ruben Smits <ruben dot smits at mech dot kuleuven dot be>

// Author: Ruben Smits <ruben dot smits at mech dot kuleuven dot be>
// Maintainer: Ruben Smits <ruben dot smits at mech dot kuleuven dot be>

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

#include <eigen_typekit/eigen_typekit.hpp>
#include <rtt/Property.hpp>
#include <rtt/PropertyBag.hpp>
#include <rtt/types/TemplateTypeInfo.hpp>
#include <rtt/types/Operators.hpp>
#include <rtt/types/OperatorTypes.hpp>
#include <rtt/types/TemplateConstructor.hpp>
#include <rtt/types/Types.hpp>
#include <rtt/Logger.hpp>
#include <rtt/internal/DataSources.hpp>
#include <rtt/internal/mystd.hpp>
#include <rtt/os/StartStopManager.hpp>
#include <rtt/types/TypekitRepository.hpp>
#include <rtt/internal/FusedFunctorDataSource.hpp>
#include <rtt/internal/DataSourceGenerator.hpp>
#include <boost/lexical_cast.hpp>

#define DECLARE_RTT_VECTOR_EXPORTS( VectorType) \
template class RTT_EXPORT RTT::internal::DataSourceTypeInfo< VectorType >; \
template class RTT_EXPORT RTT::internal::DataSource< VectorType >; \
template class RTT_EXPORT RTT::internal::AssignableDataSource< VectorType >; \
template class RTT_EXPORT RTT::internal::AssignCommand< VectorType >; \
template class RTT_EXPORT RTT::internal::ValueDataSource< VectorType >; \
template class RTT_EXPORT RTT::internal::ConstantDataSource< VectorType >; \
template class RTT_EXPORT RTT::internal::ReferenceDataSource< VectorType >; \
template class RTT_EXPORT RTT::OutputPort< VectorType >; \
template class RTT_EXPORT RTT::InputPort< VectorType >; \
template class RTT_EXPORT RTT::Property< VectorType >; \
template class RTT_EXPORT RTT::Attribute< VectorType >; \
template class RTT_EXPORT RTT::Constant< VectorType >;

DECLARE_RTT_VECTOR_EXPORTS( Eigen::VectorXd )
DECLARE_RTT_VECTOR_EXPORTS( Eigen::Vector2d )
DECLARE_RTT_VECTOR_EXPORTS( Eigen::Vector3d )
DECLARE_RTT_VECTOR_EXPORTS( Eigen::Vector4d )

template class RTT_EXPORT RTT::internal::DataSourceTypeInfo< Eigen::MatrixXd >;
template class RTT_EXPORT RTT::internal::DataSource< Eigen::MatrixXd >;
template class RTT_EXPORT RTT::internal::AssignableDataSource< Eigen::MatrixXd >;
template class RTT_EXPORT RTT::internal::AssignCommand< Eigen::MatrixXd >;
template class RTT_EXPORT RTT::internal::ValueDataSource< Eigen::MatrixXd >;
template class RTT_EXPORT RTT::internal::ConstantDataSource< Eigen::MatrixXd >;
template class RTT_EXPORT RTT::internal::ReferenceDataSource< Eigen::MatrixXd >;
template class RTT_EXPORT RTT::OutputPort< Eigen::MatrixXd >;
template class RTT_EXPORT RTT::InputPort< Eigen::MatrixXd >;
template class RTT_EXPORT RTT::Property< Eigen::MatrixXd >;
template class RTT_EXPORT RTT::Attribute< Eigen::MatrixXd >;
template class RTT_EXPORT RTT::Constant< Eigen::MatrixXd >;


#include <Eigen/Core>
namespace Eigen{

    using namespace RTT;
    using namespace RTT::detail;
    using namespace RTT::types;

    std::istream& operator>>(std::istream &is,MatrixXd& v){
      return is;
    }

#define DECLARE_VECTOR_GET_FUNCTIONS(VectorType) \
    std::istream& operator>>(std::istream &is,VectorType& v){ \
      return is; \
    } \
    double& get_item(VectorType& v, int index) \
    { \
        if (index >= (int) (v.size()) || index < 0) \
            return RTT::internal::NA<double&>::na(); \
        return v[index]; \
    } \
    double get_item_copy(const VectorType& v, int index) \
    { \
        if (index >= (int) (v.size()) || index < 0) \
            return RTT::internal::NA<double>::na(); \
        return v[index]; \
    } \
    int get_size(const VectorType& v) \
    { \
        return v.size(); \
    }
    
    DECLARE_VECTOR_GET_FUNCTIONS( Eigen::VectorXd )
    DECLARE_VECTOR_GET_FUNCTIONS( Eigen::Vector2d )
    DECLARE_VECTOR_GET_FUNCTIONS( Eigen::Vector3d )
    DECLARE_VECTOR_GET_FUNCTIONS( Eigen::Vector4d )
    

    template<class VectorType>
    struct VectorTypeInfo : public types::TemplateTypeInfo<VectorType,true>
#if (RTT_VERSION_MAJOR*100+RTT_VERSION_MINOR) >= 206
                          , public MemberFactory
#endif
    {
        VectorTypeInfo(const std::string& type_name):TemplateTypeInfo<VectorType, true >(type_name), type_name_(type_name)
        {
        };
        
        const std::string type_name_; 
        
#if (RTT_VERSION_MAJOR*100+RTT_VERSION_MINOR) >= 206
        bool installTypeInfoObject(TypeInfo* ti) {
            // aquire a shared reference to the this object
            typedef typename boost::shared_ptr< VectorTypeInfo > sh_ptr;
            sh_ptr mthis = boost::dynamic_pointer_cast<VectorTypeInfo >( this->getSharedPtr() );
            
            assert(mthis);
            // Allow base to install first
            TemplateTypeInfo<VectorType,true>::installTypeInfoObject(ti);
            // Install the factories for primitive types
            ti->setMemberFactory( mthis );
            // Don't delete us, we're memory-managed.
            return false;
        }
#endif

        bool resize(base::DataSourceBase::shared_ptr arg, int size) const
        {
            if (arg->isAssignable()) {
	        typedef typename RTT::internal::AssignableDataSource<VectorType>::shared_ptr sh_ptr;
            sh_ptr asarg = RTT::internal::AssignableDataSource<VectorType>::narrow( arg.get() );
                asarg->set().resize( size );
                asarg->updated();
                return true;
            }
            return false;
        }

        virtual std::vector<std::string> getMemberNames() const {
            // only discover the parts of this struct:
            std::vector<std::string> result;
            result.push_back("size");
            result.push_back("capacity");
            return result;
        }

        base::DataSourceBase::shared_ptr getMember(base::DataSourceBase::shared_ptr item, const std::string& name) const {
            // the only thing we do is to check for an integer in name, otherwise, assume a part (size) is accessed:
            try {
                unsigned int indx = boost::lexical_cast<unsigned int>(name);
                // @todo could also return a direct reference to item indx using another DS type that respects updated().
                return getMember( item, new RTT::internal::ConstantDataSource<int>(indx));
            } catch(...) {}

            return getMember( item, new RTT::internal::ConstantDataSource<std::string>(name) );
        }

        base::DataSourceBase::shared_ptr getMember(base::DataSourceBase::shared_ptr item,
                                                   base::DataSourceBase::shared_ptr id) const {
            // discover if user gave us a part name or index:
            RTT::internal::DataSource<int>::shared_ptr id_indx = RTT::internal::DataSource<int>::narrow( RTT::internal::DataSourceTypeInfo<int>::getTypeInfo()->convert(id).get() );
            RTT::internal::DataSource<std::string>::shared_ptr id_name = RTT::internal::DataSource<std::string>::narrow( id.get() );
            if ( id_name ) {
                if ( id_name->get() == "size" || id_name->get() == "capacity") {
                    try {
                        int (*get_size_pf)(const VectorType&) = get_size;
                        return RTT::internal::newFunctorDataSource(get_size_pf, RTT::internal::GenerateDataSource()(item.get()) );
                    } catch(...) {}
                }
            }

            if ( id_indx ) {
                try {
                    if ( item->isAssignable() )
                    {
                        double& (*get_item_pf)(VectorType&,int) = get_item;
                        return RTT::internal::newFunctorDataSource(get_item_pf, RTT::internal::GenerateDataSource()(item.get(), id_indx.get() ) );
                    }
                    else
                    {
                        double (*get_item_copy_pf)(const VectorType&,int) = get_item_copy;
                        return RTT::internal::newFunctorDataSource(get_item_copy_pf, RTT::internal::GenerateDataSource()(item.get(), id_indx.get() ) );
                    }
                } catch(...) {}
            }
            if (id_name) {
                log(Error) << "EigenVectorTypeInfo: No such member : " << id_name->get() << endlog();
            }
            if (id_indx) {
                log(Error) << "EigenVectorTypeInfo: Invalid index : " << id_indx->get() <<":"<< id_indx->getTypeName() << endlog();
            }
            if ( !id_name && ! id_indx)
                log(Error) << "EigenVectorTypeInfo: Not a member or index : " << id <<":"<< id->getTypeName() << endlog();
            return base::DataSourceBase::shared_ptr();
        }


        virtual bool decomposeTypeImpl(const VectorType& vec, PropertyBag& targetbag) const
        {
            targetbag.setType(type_name_);
            int dimension = vec.rows();
            std::string str;

            if(!targetbag.empty())
                return false;

            for ( int i=0; i < dimension ; i++){
                std::stringstream out;
                out << i+1;
                str = out.str();
                targetbag.add( new Property<double>(str, str +"th element of vector",vec(i)) ); // Put variables in the bag
            }

            return true;
        };

      virtual bool composeTypeImpl(const PropertyBag& bag, VectorType& result) const{

            if ( bag.getType() == type_name_ ) {
                int dimension = bag.size();
                result.resize( dimension );

                // Get values
                for (int i = 0; i < dimension ; i++) {
                    std::stringstream out;
                    out << i+1;
                    Property<double> elem = bag.getProperty(out.str());
                    if(elem.ready())
                        result(i) = elem.get();
                    else{
                        log(Error)<<"Could not read element "<<i+1<<endlog();
                        return false;
                    }
                }
            }else{
                log(Error) << "Composing Property< VectorType > :"
                           << " type mismatch, got type '"<< bag.getType()
                           << "', expected type "<<"eigen_vector."<<endlog();
                return false;
            }
            return true;
        };
    };

    struct MatrixTypeInfo : public types::TemplateTypeInfo<MatrixXd,true>{
        MatrixTypeInfo():TemplateTypeInfo<MatrixXd, true >("eigen_matrix"){
        };


        bool decomposeTypeImpl(const MatrixXd& mat, PropertyBag& targetbag) const{
            targetbag.setType("eigen_matrix");
            unsigned int dimension = mat.rows();
            if(!targetbag.empty())
                return false;

            for ( unsigned int i=0; i < dimension ; i++){
                std::stringstream out;
                out << i+1;
                targetbag.add( new Property<VectorXd >(out.str(), out.str() +"th row of matrix",mat.row(i) )); // Put variables in the bag
            }

            return true;
        };

        bool composeTypeImpl(const PropertyBag& bag, MatrixXd& result) const{
            if ( bag.getType() == "eigen_matrix" ) {
                unsigned int rows = bag.size();
                unsigned int cols = 0;
                // Get values
                for (unsigned int i = 0; i < rows ; i++) {
                    std::stringstream out;
                    out << i+1;
                    Property<PropertyBag> row_bag =  bag.getProperty(out.str());
                    if(!row_bag.ready()){
                        log(Error)<<"Could not read row "<<i+1<<endlog();
                        return false;
                    }
                    Property<VectorXd > row_p(row_bag.getName(),row_bag.getDescription());
                    if(!(row_p.compose(row_bag))){
                        log(Error)<<"Could not compose row "<<i+1<<endlog();
                        return false;
                    }
                    if(row_p.ready()){
                        if(i==0){
                            cols = row_p.get().size();
                            result.resize(rows,cols);
                        } else
                            if(row_p.get().rows()!=(int)cols){
                                log(Error)<<"Row "<<i+1<<" size does not match matrix columns"<<endlog();
                                return false;
                            }
                        result.row(i)=row_p.get();
                    }else{
                        log(Error)<<"Property of Row "<<i+1<<"was not ready for use"<<endlog();
                        return false;
                    }
                }
            }else {
                log(Error) << "Composing Property< MatrixXd > :"
                           << " type mismatch, got type '"<< bag.getType()
                           << "', expected type "<<"ublas_matrix."<<endlog();
                return false;
            }
            return true;
        };
    };

    template<class VectorType>
    struct vector_index
        : public std::binary_function<const VectorType&, int, double>
    {
        double operator()(const VectorType& v, int index) const
        {
            if ( index >= (int)(v.size()) || index < 0)
                return 0.0;
            return v(index);
        }
    };

    struct get_size
        : public std::unary_function<const VectorXd&, int>
    {
        int operator()(const VectorXd& cont ) const
        {
            return cont.rows();
        }
    };

    template<class VectorType>
    struct vector_index_value_constructor
        : public std::binary_function<int,double,const VectorType&>
    {
        typedef const VectorType& (Signature)( int, double );
        mutable boost::shared_ptr< VectorType > ptr;
        vector_index_value_constructor() :
            ptr( new VectorType ){}
        const VectorType& operator()(int size,double value ) const
        {
            ptr->resize(size);
            (*ptr)=VectorType::Constant(size,value);
            return *(ptr);
        }
    };

    template<class VectorType>
    struct vector_index_array_constructor
        : public std::unary_function<std::vector<double >,const VectorType&>
    {
        typedef const VectorType& (Signature)( std::vector<double > );
        mutable boost::shared_ptr< VectorType > ptr;
        vector_index_array_constructor() :
            ptr( new VectorType ){}
        const VectorType& operator()(std::vector<double > values) const
        {
            (*ptr)=VectorType::Map(&values[0],values.size());
            return *(ptr);
        }
    };

    template<class VectorType>
    struct vector_index_constructor
        : public std::unary_function<int,const VectorType&>
    {
        typedef const VectorType& (Signature)( int );
        mutable boost::shared_ptr< VectorType > ptr;
        vector_index_constructor() :
            ptr( new VectorType() ){}
        const VectorType& operator()(int size ) const
        {
            ptr->resize(size);
            return *(ptr);
        }
    };

    struct matrix_index
        : public std::ternary_function<const MatrixXd&, int, int, double>
    {
        double operator()(const MatrixXd& m, int i, int j) const{
            if ( i >= (int)(m.rows()) || i < 0 || j<0 || j>= (int)(m.cols()))
                return 0.0;
            return m(i,j);
        }
    };

    struct matrix_i_j_constructor
        : public std::binary_function<int,int,const MatrixXd&>
    {
        typedef const MatrixXd& (Signature)( int, int );
        mutable boost::shared_ptr< MatrixXd > ptr;
        matrix_i_j_constructor() :
            ptr( new MatrixXd() ){}
        const MatrixXd& operator()(int size1,int size2) const
        {
            ptr->resize(size1,size2);
            return *(ptr);
        }
    };


    std::string EigenTypekitPlugin::getName()
    {
        return "Eigen";
    }

    bool EigenTypekitPlugin::loadTypes()
    {
        RTT::types::TypeInfoRepository::Instance()->addType( new VectorTypeInfo<VectorXd>("eigen_vector") );
        RTT::types::TypeInfoRepository::Instance()->addType( new VectorTypeInfo<Vector2d>("eigen_vector2") );
        RTT::types::TypeInfoRepository::Instance()->addType( new VectorTypeInfo<Vector3d>("eigen_vector3") );
        RTT::types::TypeInfoRepository::Instance()->addType( new VectorTypeInfo<Vector4d>("eigen_vector4") );
        RTT::types::TypeInfoRepository::Instance()->addType( new MatrixTypeInfo() );
        return true;
    }

    bool EigenTypekitPlugin::loadConstructors()
    {
        RTT::types::Types()->type("eigen_vector")->addConstructor(types::newConstructor(vector_index_constructor<VectorXd>()));
        RTT::types::Types()->type("eigen_vector2")->addConstructor(types::newConstructor(vector_index_constructor<Vector2d>()));
        RTT::types::Types()->type("eigen_vector3")->addConstructor(types::newConstructor(vector_index_constructor<Vector3d>()));
        RTT::types::Types()->type("eigen_vector4")->addConstructor(types::newConstructor(vector_index_constructor<Vector4d>()));
        RTT::types::Types()->type("eigen_vector")->addConstructor(types::newConstructor(vector_index_value_constructor<VectorXd>()));
        RTT::types::Types()->type("eigen_vector")->addConstructor(types::newConstructor(vector_index_array_constructor<VectorXd>()));
        RTT::types::Types()->type("eigen_vector2")->addConstructor(types::newConstructor(vector_index_value_constructor<Vector2d>()));
        RTT::types::Types()->type("eigen_vector2")->addConstructor(types::newConstructor(vector_index_array_constructor<Vector2d>()));
        RTT::types::Types()->type("eigen_vector3")->addConstructor(types::newConstructor(vector_index_value_constructor<Vector3d>()));
        RTT::types::Types()->type("eigen_vector3")->addConstructor(types::newConstructor(vector_index_array_constructor<Vector3d>()));
        RTT::types::Types()->type("eigen_vector4")->addConstructor(types::newConstructor(vector_index_value_constructor<Vector4d>()));
        RTT::types::Types()->type("eigen_vector4")->addConstructor(types::newConstructor(vector_index_array_constructor<Vector4d>()));
        RTT::types::Types()->type("eigen_matrix")->addConstructor(types::newConstructor(matrix_i_j_constructor()));
        return true;
    }

    bool EigenTypekitPlugin::loadOperators()
    {
        RTT::types::OperatorRepository::Instance()->add( newBinaryOperator( "[]", vector_index<VectorXd>() ) );
        RTT::types::OperatorRepository::Instance()->add( newBinaryOperator( "[]", vector_index<Vector2d>() ) );
        RTT::types::OperatorRepository::Instance()->add( newBinaryOperator( "[]", vector_index<Vector3d>() ) );
        RTT::types::OperatorRepository::Instance()->add( newBinaryOperator( "[]", vector_index<Vector4d>() ) );
        //RTT::types::OperatorRepository::Instance()->add( newDotOperator( "size", get_size() ) );
        //RTT::types::OperatorRepository::Instance()->add( newTernaryOperator( "[,]", matrix_index() ) );
        return true;
    }
}

ORO_TYPEKIT_PLUGIN(Eigen::EigenTypekitPlugin)
