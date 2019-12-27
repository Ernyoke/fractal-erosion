#include "Renderer.h"

#include "ErrorHandler.h"

#include <memory>

Renderer::Renderer() {
    glCall(glEnable(GL_DEPTH_TEST));
    glCall(glDepthFunc(GL_LEQUAL));
}

Renderer::~Renderer() = default;

void Renderer::clear() const {
    glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::draw(const Terrain &terrain, const std::unique_ptr<ShaderProgram> &shader_program) const {
    shader_program->bind();
    terrain.bind();

    glCall(glDrawElements(GL_TRIANGLES, terrain.getNumberOfVertices(), GL_UNSIGNED_INT, nullptr));
}
