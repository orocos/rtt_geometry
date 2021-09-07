cmake_minimum_required(VERSION 2.8.3)
project(eigen_typekit)

find_package(Eigen3 QUIET)

if(NOT EIGEN3_FOUND)
  # Fallback to cmake_modules
  find_package(cmake_modules REQUIRED)
  find_package(Eigen REQUIRED)
  set(EIGEN3_INCLUDE_DIRS ${EIGEN_INCLUDE_DIRS})
  set(EIGEN3_LIBRARIES ${EIGEN_LIBRARIES})  # Not strictly necessary as Eigen is head only
  # Possibly map additional variables to the EIGEN3_ prefix.
else()
  set(EIGEN3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
endif()
# Use ${EIGEN3_...} variables in either case below

add_definitions(${EIGEN3_DEFINITIONS})
include_directories(${EIGEN3_INCLUDE_DIRS})

find_package(OROCOS-RTT REQUIRED)
include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake )

add_definitions(${EIGEN3_DEFINITIONS})
include_directories(
  include/orocos
  ${EIGEN3_INCLUDE_DIRS}
)

add_subdirectory(mqueue)
add_subdirectory(corba)

orocos_typekit(eigen_typekit eigen_typekit.cpp)

orocos_install_headers(include/orocos/eigen_typekit/eigen_typekit.hpp)

orocos_generate_package()
