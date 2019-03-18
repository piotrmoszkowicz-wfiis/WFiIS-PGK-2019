cmake_minimum_required(VERSION 3.2)
project(Lab02)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES lab02.cpp window.h circle.h menu.h slider.h font.h)

add_definitions(-DDEBUG)

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)
add_executable(Lab02 ${SOURCE_FILES})
target_link_libraries(Lab02 sfml-graphics sfml-window m)