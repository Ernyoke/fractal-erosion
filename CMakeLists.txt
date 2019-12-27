cmake_minimum_required(VERSION 3.15)
project(fractals)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
