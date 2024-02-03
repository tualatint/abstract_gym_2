cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

project(Gym)

find_package(OpenCV REQUIRED)
find_library(HIREDIS hiredis)
find_package(Protobuf REQUIRED)
find_package(yaml-cpp REQUIRED)
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )
set(UUID_INCLUDE_DIR "/usr/include/")
set(UUID_LIBRARY "/usr/lib/x86_64-linux-gnu/libuuid.so")

include_directories(${PROTOBUF_INCLUDE_DIRS} ${UUID_INCLUDE_DIR})
include_directories(.)

add_executable(gym2 gym2.cpp robot/two_joint_robot.cpp env/env.cpp datatype/robot_data.pb.cc)
add_executable(gym gym.cpp robot/two_joint_robot.cpp env/env.cpp datatype/robot_data.pb.cc)
add_executable(gym3 gym3.cpp robot/two_joint_robot.cpp env/env.cpp datatype/robot_data.pb.cc)

target_link_libraries(gym ${OpenCV_LIBS} ${HIREDIS} ${PROTOBUF_LIBRARIES} ${UUID_LIBRARY} ${ZeroMQ_LIBRARY} yaml-cpp)
target_link_libraries(gym3 ${OpenCV_LIBS} ${HIREDIS} ${PROTOBUF_LIBRARIES} ${UUID_LIBRARY} ${ZeroMQ_LIBRARY} yaml-cpp)
target_link_libraries(gym2 ${OpenCV_LIBS} ${HIREDIS} ${PROTOBUF_LIBRARIES} ${UUID_LIBRARY} ${ZeroMQ_LIBRARY} yaml-cpp)