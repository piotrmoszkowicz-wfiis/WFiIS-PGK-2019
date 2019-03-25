cmake_minimum_required(VERSION 3.13)
project(Lab03)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets COMPONENTS base core stc aui REQUIRED)
include_directories(/usr/local/Cellar/wxmac/3.0.4_1/lib/wx/include/osx_cocoa-unicode-3.0/)
include_directories(/usr/local/Cellar/wxmac/3.0.4_1/include/wx-3.0)

add_definitions(-I/usr/local/lib/wx/include/osx_cocoa-unicode-3.0 -I/usr/local/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__)
add_executable(Lab03 main.cpp main.h)
target_link_libraries(Lab03 ${wxWidgets_LIBRARIES})

#configure_file(${PROJECT_SOURCE_DIR}/assets/banan.png assets/banan.png COPYONLY)