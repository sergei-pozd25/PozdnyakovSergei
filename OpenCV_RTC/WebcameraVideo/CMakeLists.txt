cmake_minimum_required(VERSION 3.25)
project(WebVideo)
add_executable(WebVideo WebVideo.cpp)

set(CMAKE_CXX_STANDARD 17)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( WebVideo ${OpenCV_LIBS} )
