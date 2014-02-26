cmake_minimum_required(VERSION 2.8.3)
project(eigen_typekit)

find_package(cmake_modules REQUIRED)

find_package(Eigen REQUIRED)
find_package(OROCOS-RTT REQUIRED)
include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake )

include_directories(${Eigen_INCLUDE_DIRS})

orocos_typekit(eigen_typekit eigen_typekit.cpp)

orocos_install_headers(eigen_typekit.hpp)

orocos_generate_package()
