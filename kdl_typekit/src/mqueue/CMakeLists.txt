find_package(OROCOS-RTT 2.0.0 COMPONENTS rtt-transport-mqueue)
#this option was set in global_rules.cmake
if(OROCOS-RTT_MQUEUE_FOUND)

  find_package(Eigen3 QUIET)
  if(NOT Eigen3_FOUND)
    find_package(cmake_modules QUIET)
    find_package(Eigen QUIET)
    if(Eigen_FOUND)
      set(EIGEN3_INCLUDE_DIRS ${Eigen_INCLUDE_DIRS})
      set(EIGEN3_DEFINITIONS ${Eigen_DEFINITIONS})
      set(EIGEN3_VERSION_STRING ${PC_EIGEN_VERSION})
    else()
      message(FATAL_ERROR "Could not find cmake package Eigen3 or Eigen, which is required for the mqueue transport plugin of build ${PROEJECT_NAME}.")
    endif()
  endif()
  message(STATUS "Found Eigen version ${EIGEN3_VERSION_STRING} at ${EIGEN3_INCLUDE_DIRS}.")
  add_definitions(${EIGEN3_DEFINITIONS})
  include_directories(${EIGEN3_INCLUDE_DIRS})

  orocos_typekit(kdl-transport-mqueue SHARED kdl_mqueue.cpp)

  target_link_libraries(kdl-transport-mqueue ${OROCOS-RTT_MQUEUE_LIBRARIES} ${orocos_kdl_LIBRARIES})

  orocos_install_headers(
    FILES ${PROJECT_SOURCE_DIR}/include/orocos/${PROJECT_NAME}/transports/mqueue/kdl_mqueue.hpp
    INSTALL include/orocos/kdl_typekit/transports/mqueue
  )

endif()
