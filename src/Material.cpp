#include "Material.h"

Material::Material(float specular_intensity, float shininess)
        : specular_intensity{specular_intensity},
          shininess{shininess} {
}

void Material::useMaterial(const std::unique_ptr<ShaderProgram> &shader_program) const {
    shader_program->setUniform1f("u_Material.specularIntensity", specular_intensity);
    shader_program->setUniform1f("u_Material.shininess", shininess);
}
