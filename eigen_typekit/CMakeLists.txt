cmake_minimum_required(VERSION 2.8.3)
project(eigen_typekit)

find_package(cmake_modules REQUIRED)

find_package(Eigen3 QUIET)
if(NOT Eigen3_FOUND)
  find_package(Eigen QUIET)
  if(Eigen_FOUND)
    set(EIGEN3_INCLUDE_DIRS ${Eigen_INCLUDE_DIRS})
    set(EIGEN3_DEFINITIONS ${Eigen_DEFINITIONS})
    set(EIGEN3_VERSION_STRING ${PC_EIGEN_VERSION})
  else()
    message(FATAL_ERROR "Could not find cmake package Eigen3 or Eigen, which is required to build ${PROEJECT_NAME}.")
  endif()
endif()
message(STATUS "Found Eigen version ${EIGEN3_VERSION_STRING} at ${EIGEN3_INCLUDE_DIRS}.")
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
