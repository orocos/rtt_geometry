orocos_use_package(ocl-deployment)
find_package(OROCOS-RTT REQUIRED rtt-marshalling)
rosbuild_add_gtest(test/typekit_test typekit_test.cpp)

target_link_libraries(test/typekit_test ${OROCOS-RTT_RTT-MARSHALLING_LIBRARY} pthread)

