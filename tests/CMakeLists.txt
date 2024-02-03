cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#####
project(LineTests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ../)

add_executable(test_line geo_unit_test.cpp)
target_link_libraries(test_line ${GTEST_LIBRARIES} pthread GTest::GTest GTest::Main)

add_test(NAME LineTests COMMAND test_line)

#####
project(RobotDataTest)

find_package(Protobuf REQUIRED)
set(UUID_INCLUDE_DIR "/usr/include/")
set(UUID_LIBRARY "/usr/lib/x86_64-linux-gnu/libuuid.so")

include_directories(${PROTOBUF_INCLUDE_DIRS} ${UUID_INCLUDE_DIR})

add_executable(robot_data_test random_robot_data_generator.cpp)

target_sources(robot_data_test PRIVATE ../datatype/robot_data.pb.cc)

find_library(HIREDIS hiredis)
target_link_libraries(robot_data_test ${HIREDIS} ${PROTOBUF_LIBRARIES} ${UUID_LIBRARY})

#####
project(EnvTest)

add_executable(env_test env_test.cpp ../env/env.cpp)

#####
project(CollisionTest)

add_executable(colision_test collision_test.cpp)