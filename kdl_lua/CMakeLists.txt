cmake_minimum_required(VERSION 2.8.3)
project(kdl_lua)

find_package(catkin REQUIRED)

find_package(OROCOS-RTT REQUIRED)
include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake )

orocos_generate_package(
  DEPENDS_TARGETS ocl kdl_typekit rtt_kdl_conversions
)
