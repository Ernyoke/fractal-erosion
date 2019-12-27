cmake_minimum_required(VERSION 3.15)
project(fractals)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
