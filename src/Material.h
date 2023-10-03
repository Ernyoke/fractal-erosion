#ifndef FRACTALS_MATERIAL_H
#define FRACTALS_MATERIAL_H

#include "ShaderProgram.h"

#include <memory>

class Material {
public:
    Material(float specular_intensity, float shininess);

    void useMaterial(const std::unique_ptr<ShaderProgram> &shader_program) const;

private:
    float specular_intensity;
    float shininess;
};


#endif //FRACTALS_MATERIAL_H
