#include "ColorHelper.h"

glm::vec4 ColorHelper::hexToRGB(uint32_t hex) {
    return {
            static_cast<float>(((hex >> 16) & 0xFF)) / 255.0f, // RED
            static_cast<float>(((hex >> 8) & 0xFF)) / 255.0f,  // GREEN
            static_cast<float>((hex & 0xFF)) / 255.0f,       // BLUE
            1.0f
    };
}