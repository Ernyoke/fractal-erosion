#ifndef FRACTALS_FRACTALRESULT_H
#define FRACTALS_FRACTALRESULT_H

#include "Vertex.h"

#include <memory>
#include <vector>

struct FractalResult {
    std::shared_ptr<std::vector<Vertex>> vertices;
    std::shared_ptr<std::vector<unsigned int>> indices;
};


#endif //FRACTALS_FRACTALRESULT_H
