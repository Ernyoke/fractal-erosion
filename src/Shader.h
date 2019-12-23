#ifndef FRACTALS_SHADER_H
#define FRACTALS_SHADER_H

#include <iostream>

#include "ShaderProgram.h"

class Shader {
public:
    Shader(std::string path, unsigned int shader_type);

    virtual ~Shader();

    void compileShader();

    void attachShader(const ShaderProgram &shaderProgram);

    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

private:
    std::string path;
    unsigned int shader_type;
    unsigned int renderer_id;

    std::string parseShader();

    unsigned int getUniformLocation(const std::string &name);
};


#endif //FRACTALS_SHADER_H
