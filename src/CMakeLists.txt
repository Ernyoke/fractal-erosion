find_package(OpenGL REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/glew-cmake build-glew-cmake)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw build-glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glm build-glm)

set(IMGUI_DIR ../external/imgui)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends src)

set(STB_DIR ../external/stb)
include_directories(${STB_DIR} src)

add_executable(${PROJECT_NAME}
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
        Material.h
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${STB_DIR}/stb_image.h
        ${STB_DIR}/stb_image.cpp
)

target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_SOURCE_DIR}/external/build/glew-cmake/include
        PRIVATE ${CMAKE_SOURCE_DIR}/external/build/glfw/include
        PRIVATE $${CMAKE_SOURCE_DIR}/external/build/glm/include)

target_link_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_SOURCE_DIR}/build/external/glew-cmake/lib)

target_link_libraries(${PROJECT_NAME}
        glfw
        glm
        libglew_static)

add_library(${CMAKE_PROJECT_NAME}-lib STATIC MathHelper.cpp MathHelper.h)