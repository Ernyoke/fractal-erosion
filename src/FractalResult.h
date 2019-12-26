#ifndef FRACTALS_FRACTALRESULT_H
#define FRACTALS_FRACTALRESULT_H

#include <memory>
#include <vector>

#include <glm/glm.hpp>

struct Vertex {
    Vertex(const glm::vec3 &coordinates, const glm::vec4 &color)
            : coordinates{coordinates}, color{color} {
    }

    glm::vec3 coordinates;
    glm::vec4 color;

    static constexpr unsigned int SIZE = 7 * sizeof(float);
};

struct FractalResult {
    std::shared_ptr<std::vector<Vertex>> vertices;
    std::shared_ptr<std::vector<unsigned int>> indices;
};


#endif //FRACTALS_FRACTALRESULT_H
