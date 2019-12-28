#ifndef FRACTALS_FRACTALRESULT_H
#define FRACTALS_FRACTALRESULT_H

#include <memory>
#include <vector>

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

struct FractalResult {
    std::shared_ptr<std::vector<Vertex>> vertices;
    std::shared_ptr<std::vector<unsigned int>> indices;
};


#endif //FRACTALS_FRACTALRESULT_H
