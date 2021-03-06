#ifndef FRACTALS_SHADER_H
#define FRACTALS_SHADER_H

#include <iostream>
#include <memory>

#include "ShaderProgram.h"

class Shader {
public:
    Shader(std::string path, unsigned int shader_type);

    Shader(const Shader &shader) = delete;

    Shader &operator=(const Shader &shader) = delete;

    virtual ~Shader() = default;

    void compileShader();

    void attachShader(const std::unique_ptr<ShaderProgram> &shaderProgram);

private:
    std::string path;
    unsigned int shader_type;
    unsigned int renderer_id;

    std::string parseShader();
};


#endif //FRACTALS_SHADER_H
