cmake_minimum_required(VERSION 2.8.3)

project(kdl_typekit)

# Defines the orocos_* cmake macros. See that file for additional
# documentation.
find_package(OROCOS-RTT REQUIRED)
include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake)

option(BUILD_LUA_RTT "Build Lua RTT bindings" ON)

find_package(orocos_kdl REQUIRED)
link_directories(${orocos_kdl_LIBRARY_DIRS})

include_directories(
  include/orocos
  ${orocos_kdl_INCLUDE_DIRS}
)

# Define the way rotation properties get written to XML
# Set one of the two options below to write them as EULER ZYX or RPY
# Set none of them to write them as matrices
#add_definitions(-DROTATION_PROPERTIES_EULER)
add_definitions(-DROTATION_PROPERTIES_RPY)

orocos_typekit(${PROJECT_NAME}
  src/kdlTypekit.cpp
  src/kdlTypekitConstructors.cpp
  src/kdlTypekitOperators.cpp
  src/kdlTypekitChain.cpp
  src/kdlTypekitFrame.cpp
  src/kdlTypekitJacobian.cpp
  src/kdlTypekitJntArray.cpp
  src/kdlTypekitJoint.cpp
  src/kdlTypekitRotation.cpp
  src/kdlTypekitSegment.cpp
  src/kdlTypekitTwist.cpp
  src/kdlTypekitVector.cpp
  src/kdlTypekitWrench.cpp
  src/motionproperties.cpp
  src/kinfamproperties.cpp
  )

target_link_libraries(${PROJECT_NAME} ${orocos_kdl_LIBRARIES})

add_subdirectory(src/corba)
add_subdirectory(src/mqueue)

if(CATKIN_ENABLE_TESTING)
  add_subdirectory(test)
endif()

if(BUILD_LUA_RTT)
  file(GLOB LUA_FILES "lua/*.lua")
  set(LUA_DESTINATION share)
  if(catkin_FOUND)
    catkin_add_env_hooks(10.${PROJECT_NAME} SHELLS sh DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/env-hooks)
    set(LUA_DESTINATION ${CATKIN_GLOBAL_SHARE_DESTINATION})
  endif()

  install(
    FILES ${LUA_FILES}
    DESTINATION ${LUA_DESTINATION}/lua/5.1/${PROJECT_NAME}/
  )
endif()


orocos_install_headers(
  FILES include/orocos/${PROJECT_NAME}/typekit/Types.hpp
  INSTALL include/orocos/${PROJECT_NAME}/typekit
)

orocos_generate_package(
  DEPENDS orocos-kdl
)
