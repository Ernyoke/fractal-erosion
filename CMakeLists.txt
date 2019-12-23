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

# glm
find_package(glm REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS}, ${OPENGL_INCLUDE_DIR}, $(GLEW_INCLUDE_DIRS))

add_executable(${PROJECT_NAME}
        src/libs/stb/stb_image.h
        src/libs/stb/stb_image.cpp
        src/libs/imgui/imconfig.h
        src/libs/imgui/imgui.h
        src/libs/imgui/imgui.cpp
        src/libs/imgui/imgui_demo.cpp
        src/libs/imgui/imgui_draw.cpp
        src/libs/imgui/imgui_internal.h
        src/libs/imgui/imgui_widgets.cpp
        src/libs/imgui/imgui_impl_glfw.h
        src/libs/imgui/imgui_impl_glfw.cpp
        src/libs/imgui/imgui_impl_opengl3.h
        src/libs/imgui/imgui_impl_opengl3.cpp
        src/libs/imgui/imstb_rectpack.h
        src/libs/imgui/imstb_textedit.h
        src/libs/imgui/imstb_truetype.h
        src/Main.cpp
        src/Camera.cpp
        src/Camera.h
        src/Shader.cpp
        src/Shader.h
        src/ErrorHandler.cpp
        src/ErrorHandler.h
        src/Renderer.cpp
        src/Renderer.h
        src/VertexBuffer.cpp
        src/VertexBuffer.h
        src/IndexBuffer.cpp
        src/IndexBuffer.h
        src/VertexArray.cpp
        src/VertexArray.h
        src/VertexBufferLayout.cpp
        src/VertexBufferLayout.h
        src/VertexBufferLayoutElement.cpp
        src/VertexBufferLayoutElement.h
        src/ShaderProgram.cpp
        src/ShaderProgram.h
        src/Texture.cpp
        src/Texture.h)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})