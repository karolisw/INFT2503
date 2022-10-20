cmake_minimum_required(VERSION 3.1)

project(assignment8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

add_executable(equals equals.cpp)
add_executable(pair pair.cpp)
