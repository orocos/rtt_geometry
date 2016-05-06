cmake_minimum_required(VERSION 2.8.3)

find_package(OROCOS-RTT REQUIRED rtt-marshalling rtt-scripting)

orocos_use_package(ocl-deployment)
include_directories(${ocl-deployment_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src)

catkin_add_gtest(typekit_test typekit_test.cpp)
target_link_libraries(typekit_test 
  ${orocos_kdl_LIBRARIES}
  ${USE_OROCOS_LIBRARIES}
  ${OROCOS-RTT_RTT_LIBRARIES}
  ${OROCOS-RTT_RTT-MARSHALLING_LIBRARY} 
  ${PROJECT_NAME}
  pthread)

catkin_add_gtest(typekit_scripting_test typekit_scripting_test.cpp WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(typekit_scripting_test 
  ${orocos_kdl_LIBRARIES}
  ${OROCOS-RTT_RTT_LIBRARIES}
  ${OROCOS-RTT_RTT-SCRIPTING_LIBRARY} 
  ${PROJECT_NAME}
  pthread)

if(OROCOS-RTT_CORBA_FOUND)
catkin_add_gtest(typekit_corba_test typekit_corba_test.cpp WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(typekit_corba_test 
  ${orocos_kdl_LIBRARIES}
  ${USE_OROCOS_LIBRARIES}
  ${OROCOS-RTT_RTT_LIBRARIES}
  ${OROCOS-RTT_CORBA_LIBRARIES}
  ${PROJECT_NAME}
  pthread)
  orocos_component(kdltypekit-testcomponent testcomponent.cpp)
endif()
