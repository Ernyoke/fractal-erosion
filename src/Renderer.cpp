#include "Renderer.h"

#include "ErrorHandler.h"

#include <memory>

Renderer::Renderer() = default;

Renderer::~Renderer() = default;

void Renderer::clear() const {
    glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void
Renderer::draw(const std::unique_ptr<Terrain> &terrain, const std::unique_ptr<ShaderProgram> &shader_program) const {
    glCall(glEnable(GL_DEPTH_TEST));
    glCall(glDepthFunc(GL_LEQUAL));

    shader_program->bind();
    terrain->bind();

    glCall(glDrawElements(GL_TRIANGLES, terrain->getNumberOfVertices(), GL_UNSIGNED_INT, nullptr));
}
