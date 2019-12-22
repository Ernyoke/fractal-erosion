cmake_minimum_required(VERSION 3.15)
project(fractals)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# OpenGL
find_package(OpenGL REQUIRED)

# PkgConfig
find_package(PkgConfig REQUIRED)

# GLEW
find_package(GLEW REQUIRED)

# GLFW
pkg_search_module(GLFW REQUIRED glfw3)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

include_directories(${GLFW_INCLUDE_DIRS}, ${OPENGL_INCLUDE_DIR}, $(GLEW_INCLUDE_DIRS))

add_executable(${PROJECT_NAME} main.cpp Camera.cpp Camera.h Shader.cpp Shader.h ErrorHandling.cpp ErrorHandling.h)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})