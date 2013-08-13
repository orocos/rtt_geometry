cmake_minimum_required(VERSION 2.8.3)
project(kdl_lua)

find_package(catkin REQUIRED kdl_typekit rtt_kdl_conversions)

catkin_package(
  DEPENDS ocl
  CATKIN_DEPENDS kdl_typekit rtt_kdl_conversions
)
