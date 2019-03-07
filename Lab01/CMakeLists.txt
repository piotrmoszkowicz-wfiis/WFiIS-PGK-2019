cmake_minimum_required(VERSION 3.2)
project(Lab01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES lab01.cpp menu.h window.h shapes.h)

add_definitions(-DDEBUG)

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)
add_executable(Lab01 ${SOURCE_FILES})
target_link_libraries(Lab01 sfml-graphics sfml-window m)