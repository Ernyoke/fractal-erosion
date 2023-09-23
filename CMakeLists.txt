cmake_minimum_required(VERSION 3.26)
project(fractal-erosion VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)