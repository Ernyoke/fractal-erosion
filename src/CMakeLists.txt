set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES ${SOURCES})

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

add_executable(${BINARY}
        libs/stb/stb_image.h
        libs/stb/stb_image.cpp
        libs/imgui/imconfig.h
        libs/imgui/imgui.h
        libs/imgui/imgui.cpp
        libs/imgui/imgui_demo.cpp
        libs/imgui/imgui_draw.cpp
        libs/imgui/imgui_internal.h
        libs/imgui/imgui_widgets.cpp
        libs/imgui/imgui_impl_glfw.h
        libs/imgui/imgui_impl_glfw.cpp
        libs/imgui/imgui_impl_opengl3.h
        libs/imgui/imgui_impl_opengl3.cpp
        libs/imgui/imstb_rectpack.h
        libs/imgui/imstb_textedit.h
        libs/imgui/imstb_truetype.h
        Main.cpp
        Camera.cpp
        Camera.h
        Shader.cpp
        Shader.h
        ErrorHandler.cpp
        ErrorHandler.h
        Renderer.cpp
        Renderer.h
        VertexBuffer.cpp
        VertexBuffer.h
        IndexBuffer.cpp
        IndexBuffer.h
        VertexArray.cpp
        VertexArray.h
        VertexBufferLayout.cpp
        VertexBufferLayout.h
        VertexBufferLayoutElement.cpp
        VertexBufferLayoutElement.h
        ShaderProgram.cpp
        ShaderProgram.h
        Texture.cpp
        Texture.h
        Display.cpp
        Display.h
        DiamondSquareFractal.cpp
        DiamondSquareFractal.h
        MathHelper.cpp
        MathHelper.h
        Mesh.h
        Vertex.h
        ColorHelper.cpp
        ColorHelper.h
        MaterialHelper.cpp
        MaterialHelper.h
        Terrain.cpp
        Terrain.h
        Light.cpp
        Light.h
        Material.cpp
        Material.h)

target_link_libraries(${BINARY} ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} pthread)

add_library(${BINARY}_lib STATIC MathHelper.cpp MathHelper.h)