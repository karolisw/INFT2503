cmake_minimum_required(VERSION 3.11-3.18)

project(Assignment6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -pthread -Wall -Wextra")

find_package(Boost 1.54.0 COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(assignment assignment.cpp)  
add_executable(web web.cpp)   

target_link_libraries(assignment ${Boost_LIBRARIES})
target_link_libraries(web ${Boost_LIBRARIES})

