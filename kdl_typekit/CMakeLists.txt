# http://ros.org/doc/groovy/api/catkin/html/user_guide/supposed.html
cmake_minimum_required(VERSION 2.8.3)

project(kdl_typekit)

find_package(catkin)

catkin_package()

# Defines the orocos_* cmake macros. See that file for additional
# documentation.
find_package(OROCOS-RTT REQUIRED)
include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake)

find_package(Orocos-KDL REQUIRED)
include_directories(${Orocos-KDL_INCLUDE_DIRS})
link_directories(${Orocos-KDL_LIBRARY_DIRS})

find_package(Eigen REQUIRED)
include_directories(${Eigen_INCLUDE_DIRS})

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

target_link_libraries(${PROJECT_NAME} ${Orocos-KDL_LIBRARIES})

add_subdirectory(test)
add_subdirectory(src/corba)

orocos_generate_package()
