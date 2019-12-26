#include "MaterialHelper.h"

#include "MathHelper.h"
#include "ColorHelper.h"

#include <cmath>

static std::unordered_map<unsigned int, glm::vec4> generateColors() {
    std::unordered_map<unsigned int, glm::vec4> height_color_map;
    height_color_map.insert(std::pair<unsigned int, glm::vec4>(0, ColorHelper::hexToRGB(0x00FA9A)));
    height_color_map.insert(std::pair<unsigned int, glm::vec4>(1, ColorHelper::hexToRGB(0x00FF66)));
    height_color_map.insert(std::pair<unsigned int, glm::vec4>(2, ColorHelper::hexToRGB(0x00FF33)));
    height_color_map.insert(std::pair<unsigned int, glm::vec4>(3, ColorHelper::hexToRGB(0x00FF00)));
    height_color_map.insert(std::pair<unsigned int, glm::vec4>(4, ColorHelper::hexToRGB(0x00FF00)));
    height_color_map.insert(std::pair<unsigned int, glm::vec4>(5, ColorHelper::hexToRGB(0x00FA9A)));
    height_color_map.insert(std::pair<unsigned int, glm::vec4>(6, ColorHelper::hexToRGB(0xD1E231)));
    height_color_map.insert(std::pair<unsigned int, glm::vec4>(7, ColorHelper::hexToRGB(0xCDC673)));
    height_color_map.insert(std::pair<unsigned int, glm::vec4>(8, ColorHelper::hexToRGB(0x8B6914)));
    height_color_map.insert(std::pair<unsigned int, glm::vec4>(9, ColorHelper::hexToRGB(0x8B4500)));
    height_color_map.insert(std::pair<unsigned int, glm::vec4>(10, ColorHelper::hexToRGB(0x5E2605)));
    return height_color_map;
}

std::unordered_map<unsigned int, glm::vec4> MaterialHelper::terrain_colors = generateColors();

glm::vec4 MaterialHelper::getTerrainColorForHeight(float height, float min_height, float max_height) {
    float normalized = MathHelper::normalize(height, min_height, max_height) * 10.0f;
    auto round = static_cast<unsigned int>(std::round(normalized));
    return terrain_colors.at(round);
}
