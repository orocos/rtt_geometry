find_package(OROCOS-RTT)

#this option was set in global_rules.cmake
if(OROCOS-RTT_MQUEUE_FOUND)
  message(STATUS "MQueue Support enabled.")

  orocos_use_package(rtt-transport-mqueue)
  orocos_typekit(eigen-transport-mqueue SHARED eigen_mqueue.cpp)

  target_link_libraries(eigen-transport-mqueue ${OROCOS-RTT_MQUEUE_LIBRARIES})
  
  install(FILES eigen_mqueue.hpp DESTINATION include/orocos/eigen_typekit/transports/mqueue)

endif()