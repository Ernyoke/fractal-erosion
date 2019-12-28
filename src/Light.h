#ifndef FRACTALS_LIGHT_H
#define FRACTALS_LIGHT_H

#include "ShaderProgram.h"

#include <glm/glm.hpp>

#include <memory>

class Light {
public:
    Light();

    Light(const glm::vec3 &color, float ambient_intensity, const glm::vec3 &direction, float diffuse_intensity);

    void useLight(const std::unique_ptr<ShaderProgram> &shader_program);

private:
    glm::vec3 color;
    float ambient_intensity;

    glm::vec3 direction;
    float diffuse_intensity;
};


#endif //FRACTALS_LIGHT_H
