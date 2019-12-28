#ifndef FRACTALS_VERTEX_H
#define FRACTALS_VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
    Vertex(const glm::vec3 &coordinates, const glm::vec4 &color, const glm::vec3 &normal)
            : coordinates{coordinates}, color{color}, normal{normal} {
    }

    glm::vec3 coordinates;
    glm::vec4 color;
    glm::vec3 normal;

    static constexpr unsigned int SIZE = 10 * sizeof(float);
};

#endif //FRACTALS_VERTEX_H
