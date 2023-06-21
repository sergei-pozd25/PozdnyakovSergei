cmake_minimum_required(VERSION 3.25)
project(Deep_image)
find_package( OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
add_executable(Deep_image Deep_image.cpp)
target_link_libraries( Deep_image ${OpenCV_LIBS})