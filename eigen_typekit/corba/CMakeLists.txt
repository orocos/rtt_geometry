find_package(OROCOS-RTT 2.0.0  COMPONENTS rtt-transport-corba)

#this option was set in global_rules.cmake
if(OROCOS-RTT_CORBA_FOUND)

  include( ${OROCOS-RTT_USE_FILE} )
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/config)
  set(ENABLE_CORBA TRUE)
  find_package(Corba REQUIRED)

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

  #This has been added in order to generate files before make -j<N>
  # make -j<N> causes corruption of generated files because of overwriting
  ADD_CUSTOM_TARGET( idl-eigen DEPENDS ${CPPS} ${HPPS} COMMENT "Generating sources from .idl files")

  INSTALL_FILES( /include/eigen/bindings/rtt/corba FILES ${HPPS})

  orocos_use_package(orocos_eigen)
  orocos_typekit(eigen-transport-corba SHARED ${CPPS} ${HPPS})
  # Is used for building  the library
  TARGET_LINK_LIBRARIES(eigen-transport-corba ${OROCOS-RTT_CORBA_LIBRARIES})

  install(FILES ${HPPS} ${IDLS} DESTINATION include/orocos/eigen_typekit/transports/corba)

endif()

