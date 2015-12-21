find_package(OROCOS-RTT 2.0.0 COMPONENTS rtt-transport-mqueue)
#this option was set in global_rules.cmake
if(OROCOS-RTT_MQUEUE_FOUND)
    
  find_package(cmake_modules REQUIRED)
  find_package(Eigen REQUIRED)
  include_directories(${Eigen_INCLUDE_DIRS})

  message(STATUS "MQueue Support enabled.")

  orocos_typekit(kdl-transport-mqueue SHARED kdl_mqueue.cpp)

  target_link_libraries(kdl-transport-mqueue ${OROCOS-RTT_MQUEUE_LIBRARIES} ${orocos_kdl_LIBRARIES})
  
  install(FILES kdl_mqueue.hpp DESTINATION include/orocos/kdl_typekit/transports/mqueue)

endif()
