cmake_minimum_required(VERSION 3.12)
project(project2)

set(CMAKE_CXX_STANDARD 11)

add_executable(project2 main.cpp serial_server.h classes.h parallel_server.cpp parallel_server.h)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")