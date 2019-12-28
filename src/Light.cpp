#include "Light.h"

#include "MathHelper.h"

Light::Light()
        : color{1.0f, 1.0f, 1.0f},
          ambient_intensity{1.0f},
          direction{0.0f, -1.0f, 0.0f}, // DOWN
          diffuse_intensity{0.0f} {
}

Light::Light(const glm::vec3 &color, float ambient_intensity, const glm::vec3 &direction, float diffuse_intensity)
        : color{MathHelper::clampBetween(0.0f, 1.0f, color.x),
                MathHelper::clampBetween(0.0f, 1.0f, color.y),
                MathHelper::clampBetween(0.0f, 1.0f, color.z)},
          ambient_intensity{ambient_intensity},
          direction{direction},
          diffuse_intensity{diffuse_intensity} {
}

void Light::useLight(const std::unique_ptr<ShaderProgram> &shader_program) {
    shader_program->setUniform3f("u_DirectionalLight.color", color);
    shader_program->setUniform1f("u_DirectionalLight.ambientIntensity", ambient_intensity);
    shader_program->setUniform3f("u_DirectionalLight.direction", direction);
    shader_program->setUniform1f("u_DirectionalLight.diffuseIntensity", diffuse_intensity);
}
