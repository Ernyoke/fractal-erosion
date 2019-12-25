#include "Display.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

int main() {
    Display display(640, 480, "Fractals");
    if (display.initialize() < 0) {
        return -1;
    }

    std::shared_ptr<Camera> camera(new Camera(glm::vec3{0, 0, -3}, 70.0f, 4.0f / 3.0f, 0.1f, 100.0f));

    display.addCamera(camera);

    float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    VertexArray vertex_array;
    VertexBuffer vertex_buffer(positions, 4 * 4 * sizeof(unsigned int));

    VertexBufferLayout vertex_buffer_layout;
    vertex_array.bind();
    vertex_buffer_layout.push<float>(2);
    vertex_buffer_layout.push<float>(2);
    vertex_array.addBuffer(vertex_buffer, vertex_buffer_layout);

    IndexBuffer index_buffer(indices, 6);
    glm::mat4 projection_matrix = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

    ShaderProgram shader_program;

    Shader vertex_shader("./res/shaders/vertex.shader", GL_VERTEX_SHADER);
    vertex_shader.compileShader();
    vertex_shader.attachShader(shader_program);

    Shader fragment_shader("./res/shaders/fragment.shader", GL_FRAGMENT_SHADER);
    fragment_shader.compileShader();
    fragment_shader.attachShader(shader_program);

    shader_program.bind();
//    shader_program.setUniform4f("u_Color", 0.2f, 0.3f, 0.9f, 1.0f);
//    shader_program.setUniformMat4f("u_MVP", projection_matrix);
    shader_program.setUniformMat4f("u_MVP", camera->getViewProjection());

    Texture texture("./res/textures/cpp_opengl_logo.jpg");
    texture.bind();
    shader_program.setUniform1i("u_Texture", 0);

    Renderer renderer;

    while (!display.isClosed()) {
        renderer.clear();

        shader_program.setUniform1i("u_Texture", 0);
        shader_program.setUniformMat4f("u_MVP", camera->getViewProjection());
        renderer.draw(vertex_array, index_buffer, shader_program);

        display.update();
    }

    return 0;
}