orocos_use_package(ocl-deployment)
find_package(OROCOS-RTT REQUIRED rtt-marshalling)
catkin_add_gtest(typekit_test typekit_test.cpp)

target_link_libraries(typekit_test ${OROCOS-RTT_RTT-MARSHALLING_LIBRARY} pthread)

