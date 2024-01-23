cmake_minimum_required(VERSION 3.10)

project(LineTests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ../)

add_executable(test_line geo_unit_test.cpp)
target_link_libraries(test_line ${GTEST_LIBRARIES} pthread GTest::GTest GTest::Main)

add_test(NAME LineTests COMMAND test_line)