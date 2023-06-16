cmake_minimum_required(VERSION 3.25)
project(VideoLoading)

set(CMAKE_CXX_STANDARD 17)

add_executable(VideoLoading VideoTest.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( VideoLoading ${OpenCV_LIBS} )

