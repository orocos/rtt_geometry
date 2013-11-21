cmake_minimum_required(VERSION 2.8.3)

find_package(OROCOS-RTT REQUIRED rtt-marshalling)

orocos_use_package(ocl-deployment)

catkin_add_gtest(typekit_test typekit_test.cpp)
target_link_libraries(typekit_test 
  ${orocos_kdl_LIBRARIES}
  ${USE_OROCOS_LIBRARIES}
  ${OROCOS-RTT_RTT_LIBRARIES}
  ${OROCOS-RTT_RTT-MARSHALLING_LIBRARY} 
  pthread)

