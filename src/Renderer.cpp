#include "Renderer.h"

#include "ErrorHandler.h"

Renderer::Renderer() {
    glCall(glEnable(GL_DEPTH_TEST));
    glCall(glDepthFunc(GL_LEQUAL));
}

Renderer::~Renderer() = default;

void Renderer::clear() const {
    glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::draw(const VertexArray &vertex_array, const IndexBuffer &index_buffer,
                    const ShaderProgram &shader_program) const {
    shader_program.bind();
    vertex_array.bind();
    index_buffer.bind();

    glCall(glDrawElements(GL_TRIANGLES, index_buffer.getCount(), GL_UNSIGNED_INT, nullptr));
}
