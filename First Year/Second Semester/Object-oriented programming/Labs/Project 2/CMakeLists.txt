cmake_minimum_required(VERSION 3.24)
project(Project_2)

set(CMAKE_CXX_STANDARD 17)

set(ENV{OPENCV_DIR} "D:\\opencv\\build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

add_executable(Project_2 main.cpp)

target_link_libraries(Project_2 ${OpenCV_LIBS})
