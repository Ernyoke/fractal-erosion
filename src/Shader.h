#ifndef FRACTALS_SHADER_H
#define FRACTALS_SHADER_H

#include <iostream>
#include <memory>

#include "ShaderProgram.h"

class Shader {
public:
    Shader(std::string source, unsigned int shader_type);

    Shader(const Shader &shader) = delete;

    Shader &operator=(const Shader &shader) = delete;

    virtual ~Shader() = default;

    void compileShader();

    void attachShader(const std::unique_ptr<ShaderProgram> &shaderProgram) const;

private:
    unsigned int shader_type;
    unsigned int renderer_id;

    std::string source;
};


#endif //FRACTALS_SHADER_H
