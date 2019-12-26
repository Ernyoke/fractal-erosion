#include "Display.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Camera.h"
#include "DiamondSquareFractal.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr float ASPECT_RATION = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);
constexpr float FIELD_OF_VIEW = 70.0f;
constexpr float Z_NEAR = 0.1f;
constexpr float Z_FAR = 500.0f;
const char *TITLE = "Fractals";

int main() {
    Display display(WIDTH, HEIGHT, TITLE);
    if (display.initialize() < 0) {
        return -1;
    }

    glm::mat4 projection = glm::perspective(FIELD_OF_VIEW, ASPECT_RATION, Z_NEAR, Z_FAR);

    std::shared_ptr<Camera> camera(
            new Camera(glm::vec3(0.0f, 10.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f));

    display.addCamera(camera);

    DiamondSquareFractal diamond_squared_fractal;
    FractalResult fractal_result = diamond_squared_fractal.generate();

    VertexArray vertex_array;
    VertexBuffer vertex_buffer(fractal_result.vertices->data(), fractal_result.vertices->size() * Vertex::SIZE);

    VertexBufferLayout vertex_buffer_layout;
    vertex_array.bind();
    vertex_buffer_layout.push<float>(3);
    vertex_buffer_layout.push<float>(4);
    vertex_array.addBuffer(vertex_buffer, vertex_buffer_layout);

    IndexBuffer index_buffer(fractal_result.indices->data(), fractal_result.indices->size());

    ShaderProgram shader_program;

    Shader vertex_shader("./res/shaders/vertex.shader", GL_VERTEX_SHADER);
    vertex_shader.compileShader();
    vertex_shader.attachShader(shader_program);

    Shader fragment_shader("./res/shaders/fragment.shader", GL_FRAGMENT_SHADER);
    fragment_shader.compileShader();
    fragment_shader.attachShader(shader_program);

    shader_program.bind();
    shader_program.setUniformMat4f("u_MVP", projection * camera->calculateViewMatrix());

    Renderer renderer;

    while (!display.isClosed()) {
        renderer.clear();
        shader_program.setUniformMat4f("u_MVP", projection * camera->calculateViewMatrix());
        renderer.draw(vertex_array, index_buffer, shader_program);

        display.update();
    }

    return 0;
}