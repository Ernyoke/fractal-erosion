#ifndef FRACTALS_MESH_H
#define FRACTALS_MESH_H

#include "Vertex.h"

#include <memory>
#include <vector>

struct Mesh {
    std::shared_ptr<std::vector<Vertex>> vertices;
    std::shared_ptr<std::vector<unsigned int>> indices;
};


#endif //FRACTALS_MESH_H
