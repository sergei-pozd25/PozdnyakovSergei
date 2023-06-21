cmake_minimum_required(VERSION 3.25)
project(PCL_Test)

find_package(PCL 1.9 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

set(CMAKE_CXX_STANDARD 17)

add_executable(PCL_Test PCL_Test.cpp PCL_Test.cpp)
target_link_libraries(PCL_Test ${PCL_LIBRARIES})
install(TARGETS PCL_Test RUNTIME DESTINATION bin)