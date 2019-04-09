cmake_minimum_required(VERSION 3.13)
project(Lab05)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets COMPONENTS base core stc aui REQUIRED)
include_directories(/usr/local/Cellar/wxmac/3.0.4_1/lib/wx/include/osx_cocoa-unicode-3.0/)
include_directories(/usr/local/Cellar/wxmac/3.0.4_1/include/wx-3.0)

add_definitions(-I/usr/local/lib/wx/include/osx_cocoa-unicode-3.0 -I/usr/local/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__)
add_executable(Lab05
        main.cpp
        GUI.h
        GUI.cpp
        GUIMyFrame1.h
        GUIMyFrame1.cpp
        vecmat.h
        vecmat.cpp
)
target_link_libraries(Lab05 ${wxWidgets_LIBRARIES})