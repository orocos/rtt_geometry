find_package(OROCOS-RTT)

#this option was set in global_rules.cmake
if(OROCOS-RTT_MQUEUE_FOUND)

  orocos_use_package(rtt-transport-mqueue)
  orocos_typekit(eigen-transport-mqueue SHARED eigen_mqueue.cpp)

  target_link_libraries(eigen-transport-mqueue ${OROCOS-RTT_MQUEUE_LIBRARIES})

  orocos_install_headers(
    FILES ../include/orocos/${PROJECT_NAME}/transports/mqueue/eigen_mqueue.hpp
    INSTALL include/orocos/${PROJECT_NAME}/transports/mqueue
  )

endif()

