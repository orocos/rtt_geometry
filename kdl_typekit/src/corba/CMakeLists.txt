find_package(OROCOS-RTT)

#this option was set in global_rules.cmake
if(OROCOS-RTT_CORBA_FOUND)

  include( ${OROCOS-RTT_USE_FILE} )
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/config)
  set(ENABLE_CORBA TRUE)
  find_package(Corba REQUIRED)

  # for jacobian and jntarray
  find_package(Eigen3 QUIET)
  if(NOT Eigen3_FOUND)
    find_package(cmake_modules QUIET)
    find_package(Eigen QUIET)
    if(Eigen_FOUND)
      set(EIGEN3_INCLUDE_DIRS ${Eigen_INCLUDE_DIRS})
      set(EIGEN3_DEFINITIONS ${Eigen_DEFINITIONS})
      set(EIGEN3_VERSION_STRING ${PC_EIGEN_VERSION})
    else()
      message(FATAL_ERROR "Could not find cmake package Eigen3 or Eigen, which is required for the CORBA transport plugin of ${PROEJECT_NAME}.")
    endif()
  endif()
  message(STATUS "Found Eigen version ${EIGEN3_VERSION_STRING} at ${EIGEN3_INCLUDE_DIRS}.")
  add_definitions(${EIGEN3_DEFINITIONS})
  include_directories(${EIGEN3_INCLUDE_DIRS})

  # Add includes / lib paths if necessary
#  IF( NOT ${ACE_DIR} STREQUAL /usr/include )
#    SET(CMAKE_C_FLAGS_RTT "${CMAKE_C_FLAGS_RTT} -I${ACE_DIR}" CACHE INTERNAL "")
#    SET(CMAKE_LINKFLAGS_RTT "${CMAKE_LINKFLAGS_RTT} -L${ACE_DIR}/../lib" CACHE INTERNAL "")
#  ENDIF( NOT ${ACE_DIR} STREQUAL /usr/include )
#  IF( NOT ${TAO_DIR} STREQUAL /usr/include )
#    SET(CMAKE_C_FLAGS_RTT "${CMAKE_C_FLAGS_RTT} -I${TAO_DIR}" CACHE INTERNAL "")
#  ENDIF( NOT ${TAO_DIR} STREQUAL /usr/include )
#  IF( NOT ${ORBSVCS_DIR} STREQUAL /usr/include )
#    SET(CMAKE_C_FLAGS_RTT "${CMAKE_C_FLAGS_RTT} -I${ORBSVCS_DIR}" CACHE INTERNAL "")
#  ENDIF( NOT ${ORBSVCS_DIR} STREQUAL /usr/include )

  FILE( GLOB IDLS
    ${PROJECT_SOURCE_DIR}/include/orocos/${PROJECT_NAME}/transports/corba/[^.]*.idl
  )
  FILE( GLOB CPPS [^.]*.cpp )
  FILE( GLOB HPPS
    ${PROJECT_SOURCE_DIR}/include/orocos/${PROJECT_NAME}/transports/corba/[^.]*.hpp
    ${PROJECT_SOURCE_DIR}/include/orocos/${PROJECT_NAME}/transports/corba/[^.]*.h
    ${PROJECT_SOURCE_DIR}/include/orocos/${PROJECT_NAME}/transports/corba/[^.]*.inl
  )

  ORO_ADD_CORBA_SERVERS(CPPS HPPS ${IDLS} )
  SET( ENV{GLOBAL_GENERATED_SRCS} "${CPPS}" )

  #This has been added in order to generate files before make -j<N>
  # make -j<N> causes corruption of generated files because of overwriting
  ADD_CUSTOM_TARGET( idl-kdl-corba DEPENDS ${CPPS} ${HPPS}
            COMMENT "Generating sources from .idl files")

  orocos_use_package(orocos_kdl)
  orocos_typekit(kdl-transport-corba SHARED ${CPPS} ${HPPS})
  # Is used for building  the library
  TARGET_LINK_LIBRARIES(kdl-transport-corba ${OROCOS-RTT_CORBA_LIBRARIES})

  install(FILES ${HPPS} ${IDLS} DESTINATION include/orocos/kdl_typekit/transports/corba)

endif()

