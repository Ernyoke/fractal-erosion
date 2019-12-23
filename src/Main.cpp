#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "ErrorHandler.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cerr << "OPENGL could not be initialized!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    VertexArray vertex_array;
    VertexBuffer vertex_buffer(positions, 4 * 2 * sizeof(unsigned int));

    VertexBufferLayout vertex_buffer_layout;
    vertex_array.bind();
    vertex_buffer_layout.push<float>(2);
    vertex_array.addBuffer(vertex_buffer, vertex_buffer_layout);

    IndexBuffer index_buffer(indices, 6);

    ShaderProgram shader_program;

    Shader vertex_shader("./res/shaders/vertex.shader", GL_VERTEX_SHADER);
    vertex_shader.compileShader();
    vertex_shader.attachShader(shader_program);

    Shader fragment_shader("./res/shaders/fragment.shader", GL_FRAGMENT_SHADER);
    fragment_shader.compileShader();
    fragment_shader.attachShader(shader_program);

    shader_program.useShaderProgram();

    int location = glGetUniformLocation(shader_program.getProgramId(), "u_Color");
    if (location >= 0) {
        glCall(glUniform4f(location, 0.2f, 0.3f, 0.9f, 1.0f));
    }

    float r = 0.0f;
    float increment = 0.05f;
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader_program.useShaderProgram();
        glCall(glUniform4f(location, r, 0.3f, 0.9f, 1.0f));

        vertex_array.bind();
        index_buffer.bind();

        glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f) {
            increment = -0.05f;
        } else {
            if (r < 0.0f) {
                increment = 0.05f;
            }
        }
        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}