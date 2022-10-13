cmake_minimum_required(VERSION 3.1)

project(assignment7)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra")

add_executable(task1 fraction.cpp task1.cpp)
# add_executable(task2 task2.cpp)