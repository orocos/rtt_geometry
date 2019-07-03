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

#define DECLARE_RTT_VECTOR_EXPORTS( VectorType ) \
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
DECLARE_RTT_VECTOR_EXPORTS( Eigen::Vector6d )

#define DECLARE_RTT_MATRIX_EXPORTS( MatrixType ) \
template class RTT_EXPORT RTT::internal::DataSourceTypeInfo< MatrixType >; \
template class RTT_EXPORT RTT::internal::DataSource< MatrixType >; \
template class RTT_EXPORT RTT::internal::AssignableDataSource< MatrixType >; \
template class RTT_EXPORT RTT::internal::AssignCommand< MatrixType >; \
template class RTT_EXPORT RTT::internal::ValueDataSource< MatrixType >; \
template class RTT_EXPORT RTT::internal::ConstantDataSource< MatrixType >; \
template class RTT_EXPORT RTT::internal::ReferenceDataSource< MatrixType >; \
template class RTT_EXPORT RTT::OutputPort< MatrixType >; \
template class RTT_EXPORT RTT::InputPort< MatrixType >; \
template class RTT_EXPORT RTT::Property< MatrixType >; \
template class RTT_EXPORT RTT::Attribute< MatrixType >; \
template class RTT_EXPORT RTT::Constant< MatrixType >;

DECLARE_RTT_MATRIX_EXPORTS( Eigen::MatrixXd )
DECLARE_RTT_MATRIX_EXPORTS( Eigen::Matrix2d )
DECLARE_RTT_MATRIX_EXPORTS( Eigen::Matrix3d )
DECLARE_RTT_MATRIX_EXPORTS( Eigen::Matrix4d )
DECLARE_RTT_MATRIX_EXPORTS( Eigen::Matrix6d )

#include <Eigen/Core>
namespace Eigen{

    using namespace RTT;
    using namespace RTT::detail;
    using namespace RTT::types;

    template<typename Derived>
    std::istream& operator>>(std::istream &is, EigenBase<Derived>& v){
      return is;
    }
    
    template<typename VectorType>
    double& get_item(VectorType& v, int index)
    {
        if (index >= (int) (v.size()) || index < 0)
            return RTT::internal::NA<double&>::na();
        return v[index];
    }
    
    template<typename VectorType>
    double get_item_copy(const VectorType& v, int index)
    {
        if (index >= (int) (v.size()) || index < 0)
            return RTT::internal::NA<double>::na();
        return v[index];
    }
    
    template<typename VectorType>
    int get_size(const VectorType& v)
    {
        return v.size();
    }

    template<class VectorType>
    struct VectorTypeInfo : public types::TemplateTypeInfo<VectorType,true>
#if (RTT_VERSION_MAJOR*100+RTT_VERSION_MINOR) >= 206
                          , public MemberFactory
#endif
    {
        VectorTypeInfo(const std::string& type_name):TemplateTypeInfo<VectorType, true >(type_name)
        {
        };
                
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
	        typedef typename RTT::internal::AssignableDataSource<VectorType >::shared_ptr sh_ptr;
            sh_ptr asarg = RTT::internal::AssignableDataSource<VectorType >::narrow( arg.get() );
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
                        return RTT::internal::newFunctorDataSource(&get_size<VectorType>, RTT::internal::GenerateDataSource()(item.get()) );
                    } catch(...) {}
                }
            }

            if ( id_indx ) {
                try {
                    if ( item->isAssignable() )
                    {
                        return RTT::internal::newFunctorDataSource(get_item<VectorType>, RTT::internal::GenerateDataSource()(item.get(), id_indx.get() ) );
                    }
                    else
                    {
                        return RTT::internal::newFunctorDataSource(get_item_copy<VectorType>, RTT::internal::GenerateDataSource()(item.get(), id_indx.get() ) );
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
            targetbag.setType(this->getTypeName());
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

            if ( bag.getType() == this->getTypeName() ) {
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
                log(Error) << "Composing Property< " << this->getTypeName() << " > :"
                           << " type mismatch, got type '"<< bag.getType()
                           << "', expected type "<<"eigen_vector."<<endlog();
                return false;
            }
            return true;
        };
    };

    template<typename MatrixType>
    struct MatrixTypeInfo : public types::TemplateTypeInfo<MatrixType,true>{
        MatrixTypeInfo(const std::string& type_name):TemplateTypeInfo<MatrixType, true >(type_name){
        };


        bool decomposeTypeImpl(const MatrixType& mat, PropertyBag& targetbag) const{
            targetbag.setType(this->getTypeName());
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

        bool composeTypeImpl(const PropertyBag& bag, MatrixType& result) const{
            if ( bag.getType() == this->getTypeName() ) {
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
                log(Error) << "Composing Property< " << this->getTypeName() << " > :"
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
    
    template<class VectorType>
    struct get_size_functor
        : public std::unary_function<const VectorType&, int>
    {
        int operator()(const VectorType& cont ) const
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
    struct vector_size_constructor
        : public std::unary_function<int,const VectorType&>
    {
        typedef const VectorType& (Signature)( int );
        mutable boost::shared_ptr< VectorType > ptr;
        vector_size_constructor() :
            ptr( new VectorType() ){}
        const VectorType& operator()(int size ) const
        {
            ptr->resize(size);
            return *(ptr);
        }
    };

    template<typename MatrixType>
    struct matrix_index_functor
        : public std::ternary_function<const MatrixType&, int, int, double>
    {
        double operator()(const MatrixType& m, int i, int j) const{
            if ( i >= (int)(m.rows()) || i < 0 || j<0 || j>= (int)(m.cols()))
                return 0.0;
            return m(i,j);
        }
    };

    template<typename MatrixType>
    struct matrix_i_j_constructor
        : public std::binary_function<int,int,const MatrixType&>
    {
        typedef const MatrixType& (Signature)( int, int );
        mutable boost::shared_ptr< MatrixType > ptr;
        matrix_i_j_constructor() :
            ptr( new MatrixType() ){}
        const MatrixType& operator()(int size1,int size2) const
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
        RTT::types::TypeInfoRepository::Instance()->addType( new VectorTypeInfo<Vector6d>("eigen_vector6") );
        RTT::types::TypeInfoRepository::Instance()->addType( new MatrixTypeInfo<MatrixXd>("eigen_matrix") );
        RTT::types::TypeInfoRepository::Instance()->addType( new MatrixTypeInfo<Matrix2d>("eigen_matrix2") );
        RTT::types::TypeInfoRepository::Instance()->addType( new MatrixTypeInfo<Matrix3d>("eigen_matrix3") );
        RTT::types::TypeInfoRepository::Instance()->addType( new MatrixTypeInfo<Matrix4d>("eigen_matrix4") );
        RTT::types::TypeInfoRepository::Instance()->addType( new MatrixTypeInfo<Matrix6d>("eigen_matrix6") );
        return true;
    }

    bool EigenTypekitPlugin::loadConstructors()
    {
        RTT::types::Types()->type("eigen_vector")->addConstructor(types::newConstructor(vector_size_constructor<VectorXd>()));
        RTT::types::Types()->type("eigen_vector")->addConstructor(types::newConstructor(vector_index_value_constructor<VectorXd>()));
        RTT::types::Types()->type("eigen_vector")->addConstructor(types::newConstructor(vector_index_array_constructor<VectorXd>()));
        RTT::types::Types()->type("eigen_vector2")->addConstructor(types::newConstructor(vector_index_value_constructor<Vector2d>()));
        RTT::types::Types()->type("eigen_vector2")->addConstructor(types::newConstructor(vector_index_array_constructor<Vector2d>()));
        RTT::types::Types()->type("eigen_vector3")->addConstructor(types::newConstructor(vector_index_value_constructor<Vector3d>()));
        RTT::types::Types()->type("eigen_vector3")->addConstructor(types::newConstructor(vector_index_array_constructor<Vector3d>()));
        RTT::types::Types()->type("eigen_vector4")->addConstructor(types::newConstructor(vector_index_value_constructor<Vector4d>()));
        RTT::types::Types()->type("eigen_vector4")->addConstructor(types::newConstructor(vector_index_array_constructor<Vector4d>()));
        RTT::types::Types()->type("eigen_vector6")->addConstructor(types::newConstructor(vector_index_value_constructor<Vector6d>()));
        RTT::types::Types()->type("eigen_vector6")->addConstructor(types::newConstructor(vector_index_array_constructor<Vector6d>()));
        RTT::types::Types()->type("eigen_matrix")->addConstructor(types::newConstructor(matrix_i_j_constructor<MatrixXd>()));
        RTT::types::Types()->type("eigen_matrix2")->addConstructor(types::newConstructor(matrix_i_j_constructor<Matrix2d>()));
        RTT::types::Types()->type("eigen_matrix3")->addConstructor(types::newConstructor(matrix_i_j_constructor<Matrix3d>()));
        RTT::types::Types()->type("eigen_matrix4")->addConstructor(types::newConstructor(matrix_i_j_constructor<Matrix4d>()));
        RTT::types::Types()->type("eigen_matrix6")->addConstructor(types::newConstructor(matrix_i_j_constructor<Matrix6d>()));
        return true;
    }

    bool EigenTypekitPlugin::loadOperators()
    {
        RTT::types::OperatorRepository::Instance()->add( newBinaryOperator( "[]", vector_index<VectorXd>() ) );
        RTT::types::OperatorRepository::Instance()->add( newBinaryOperator( "[]", vector_index<Vector2d>() ) );
        RTT::types::OperatorRepository::Instance()->add( newBinaryOperator( "[]", vector_index<Vector3d>() ) );
        RTT::types::OperatorRepository::Instance()->add( newBinaryOperator( "[]", vector_index<Vector4d>() ) );
        RTT::types::OperatorRepository::Instance()->add( newBinaryOperator( "[]", vector_index<Vector6d>() ) );
        //RTT::types::OperatorRepository::Instance()->add( newDotOperator( "size", get_size() ) );
        //RTT::types::OperatorRepository::Instance()->add( newTernaryOperator( "[,]", matrix_index() ) );
        return true;
    }
}

ORO_TYPEKIT_PLUGIN(Eigen::EigenTypekitPlugin)
