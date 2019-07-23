/*
 * (C) 2010 Ruben Smits, ruben.smits@mech.kuleuven.be, Department of Mechanical
 Engineering, Katholieke Universiteit Leuven, Belgium.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

 Alternatively, the contents of this file may be used under the terms of
 either of the New BSD License
 */
#ifndef EIGEN_TYPEKIT_HPP
#define EIGEN_TYPEKIT_HPP

#include <rtt/types/TypekitPlugin.hpp>
#include <Eigen/Core>

// import most common Eigen types 
namespace Eigen {

typedef Matrix<double,6,1> Vector6d;

class EigenTypekitPlugin: public RTT::types::TypekitPlugin {
public:
	virtual std::string getName();

	virtual bool loadTypes();
	virtual bool loadConstructors();
	virtual bool loadOperators();
};
}

#ifdef CORELIB_DATASOURCE_HPP
#define DECLARE_VECTOR_CORELIB_DATASOURCE_HPP(VectorType) \
    extern template class RTT::internal::DataSourceTypeInfo< VectorType >; \
    extern template class RTT::internal::DataSource< VectorType >; \
    extern template class RTT::internal::AssignableDataSource< VectorType >; \
    extern template class RTT::internal::AssignCommand< VectorType >;

    DECLARE_VECTOR_CORELIB_DATASOURCE_HPP(Eigen::VectorXd)
    DECLARE_VECTOR_CORELIB_DATASOURCE_HPP(Eigen::Vector2d)
    DECLARE_VECTOR_CORELIB_DATASOURCE_HPP(Eigen::Vector3d)
    DECLARE_VECTOR_CORELIB_DATASOURCE_HPP(Eigen::Vector4d)
    DECLARE_VECTOR_CORELIB_DATASOURCE_HPP(Eigen::Vector6d)
#endif

#ifdef ORO_CORELIB_DATASOURCES_HPP
#define DECLARE_VECTOR_ORO_CORELIB_DATASOURCES_HPP(VectorType) \
    extern template class RTT::internal::ValueDataSource< VectorType >; \
    extern template class RTT::internal::ConstantDataSource< VectorType >; \
    extern template class RTT::internal::ReferenceDataSource< VectorType >;
    
    DECLARE_VECTOR_ORO_CORELIB_DATASOURCES_HPP(Eigen::VectorXd)
    DECLARE_VECTOR_ORO_CORELIB_DATASOURCES_HPP(Eigen::Vector2d)
    DECLARE_VECTOR_ORO_CORELIB_DATASOURCES_HPP(Eigen::Vector3d)
    DECLARE_VECTOR_ORO_CORELIB_DATASOURCES_HPP(Eigen::Vector4d)
    DECLARE_VECTOR_ORO_CORELIB_DATASOURCES_HPP(Eigen::Vector6d)
#endif

#ifdef ORO_OUTPUT_PORT_HPP
    extern template class RTT::OutputPort< Eigen::VectorXd >;
    extern template class RTT::OutputPort< Eigen::Vector2d >;
    extern template class RTT::OutputPort< Eigen::Vector3d >;
    extern template class RTT::OutputPort< Eigen::Vector4d >;
    extern template class RTT::OutputPort< Eigen::Vector6d >;
#endif

#ifdef ORO_INPUT_PORT_HPP
    extern template class RTT::InputPort< Eigen::VectorXd >;
    extern template class RTT::InputPort< Eigen::Vector2d >;
    extern template class RTT::InputPort< Eigen::Vector3d >;
    extern template class RTT::InputPort< Eigen::Vector4d >;
    extern template class RTT::InputPort< Eigen::Vector6d >;
#endif

#ifdef ORO_PROPERTY_HPP
    extern template class RTT::Property< Eigen::VectorXd >;
    extern template class RTT::Property< Eigen::Vector2d >;
    extern template class RTT::Property< Eigen::Vector3d >;
    extern template class RTT::Property< Eigen::Vector4d >;
    extern template class RTT::Property< Eigen::Vector6d >;
#endif

#ifdef ORO_CORELIB_ATTRIBUTE_HPP
#define DECLARE_VECTOR_ORO_CORELIB_ATTRIBUTE_HPP(VectorType) \
    extern template class RTT::Attribute< VectorType >; \
    extern template class RTT::Constant< VectorType >;
    
    DECLARE_VECTOR_ORO_CORELIB_ATTRIBUTE_HPP(Eigen::VectorXd)
    DECLARE_VECTOR_ORO_CORELIB_ATTRIBUTE_HPP(Eigen::Vector2d)
    DECLARE_VECTOR_ORO_CORELIB_ATTRIBUTE_HPP(Eigen::Vector3d)
    DECLARE_VECTOR_ORO_CORELIB_ATTRIBUTE_HPP(Eigen::Vector4d)
    DECLARE_VECTOR_ORO_CORELIB_ATTRIBUTE_HPP(Eigen::Vector6d)
#endif


#ifdef CORELIB_DATASOURCE_HPP
#define DECLARE_MATRIX_CORELIB_DATASOURCE_HPP(MatrixType) \
    extern template class RTT::internal::DataSourceTypeInfo< MatrixType >; \
    extern template class RTT::internal::DataSource< MatrixType >; \
    extern template class RTT::internal::AssignableDataSource< MatrixType >; \
    extern template class RTT::internal::AssignCommand< MatrixType >;
    
    DECLARE_MATRIX_CORELIB_DATASOURCE_HPP(Eigen::MatrixXd)
    DECLARE_MATRIX_CORELIB_DATASOURCE_HPP(Eigen::Matrix2d)
    DECLARE_MATRIX_CORELIB_DATASOURCE_HPP(Eigen::Matrix3d)
    DECLARE_MATRIX_CORELIB_DATASOURCE_HPP(Eigen::Matrix4d)
#endif
#ifdef ORO_CORELIB_DATASOURCES_HPP
#define DECLARE_MATRIX_ORO_CORELIB_DATASOURCES_HPP(MatrixType) \
    extern template class RTT::internal::ValueDataSource< MatrixType >; \
    extern template class RTT::internal::ConstantDataSource< MatrixType >; \
    extern template class RTT::internal::ReferenceDataSource< MatrixType >;
    
    DECLARE_MATRIX_CORELIB_DATASOURCE_HPP(Eigen::MatrixXd)
    DECLARE_MATRIX_CORELIB_DATASOURCE_HPP(Eigen::Matrix2d)
    DECLARE_MATRIX_CORELIB_DATASOURCE_HPP(Eigen::Matrix3d)
    DECLARE_MATRIX_CORELIB_DATASOURCE_HPP(Eigen::Matrix4d)
#endif
#ifdef ORO_OUTPUT_PORT_HPP
    extern template class RTT::OutputPort< Eigen::MatrixXd >;
    extern template class RTT::OutputPort< Eigen::Matrix2d >;
    extern template class RTT::OutputPort< Eigen::Matrix3d >;
    extern template class RTT::OutputPort< Eigen::Matrix4d >;
#endif
#ifdef ORO_INPUT_PORT_HPP
    extern template class RTT::InputPort< Eigen::MatrixXd >;
    extern template class RTT::InputPort< Eigen::Matrix2d >;
    extern template class RTT::InputPort< Eigen::Matrix3d >;
    extern template class RTT::InputPort< Eigen::Matrix4d >;
#endif
#ifdef ORO_PROPERTY_HPP
    extern template class RTT::Property< Eigen::MatrixXd >;
    extern template class RTT::Property< Eigen::Matrix2d >;
    extern template class RTT::Property< Eigen::Matrix3d >;
    extern template class RTT::Property< Eigen::Matrix4d >;
#endif
#ifdef ORO_CORELIB_ATTRIBUTE_HPP
#define DECLARE_MATRIX_ORO_CORELIB_ATTRIBUTE_HPP(MatrixType) \
    extern template class RTT::Attribute< MatrixType >; \
    extern template class RTT::Constant< MatrixType >;
    
    DECLARE_MATRIX_ORO_CORELIB_ATTRIBUTE_HPP(Eigen::MatrixXd)
    DECLARE_MATRIX_ORO_CORELIB_ATTRIBUTE_HPP(Eigen::Matrix2d)
    DECLARE_MATRIX_ORO_CORELIB_ATTRIBUTE_HPP(Eigen::Matrix3d)
    DECLARE_MATRIX_ORO_CORELIB_ATTRIBUTE_HPP(Eigen::Matrix4d)
#endif

#endif // ifndef EIGEN_TYPEKIT_HPP

