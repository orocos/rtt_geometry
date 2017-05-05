find_package(OROCOS-RTT 2.0.0 COMPONENTS rtt-transport-mqueue)
#this option was set in global_rules.cmake
if(OROCOS-RTT_MQUEUE_FOUND)

  find_package(cmake_modules REQUIRED)
  find_package(Eigen REQUIRED)
  include_directories(${Eigen_INCLUDE_DIRS})

  orocos_typekit(kdl-transport-mqueue SHARED kdl_mqueue.cpp)

  target_link_libraries(kdl-transport-mqueue ${OROCOS-RTT_MQUEUE_LIBRARIES} ${orocos_kdl_LIBRARIES})

  orocos_install_headers(
    FILES ${PROJECT_SOURCE_DIR}/include/orocos/${PROJECT_NAME}/transports/mqueue/kdl_mqueue.hpp
    INSTALL include/orocos/kdl_typekit/transports/mqueue
  )

endif()
