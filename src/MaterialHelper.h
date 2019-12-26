#ifndef FRACTALS_MATERIALHELPER_H
#define FRACTALS_MATERIALHELPER_H

#include <unordered_map>

#include <glm/glm.hpp>

class MaterialHelper {
public:
    static glm::vec4 getTerrainColorForHeight(float height, float min_height, float max_height);

private:
    static std::unordered_map<unsigned int, glm::vec4> terrain_colors;
};


#endif //FRACTALS_MATERIALHELPER_H
