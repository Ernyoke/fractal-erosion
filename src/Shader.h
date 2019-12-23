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

private:
    std::string path;
    unsigned int shader_type;
    unsigned int renderer_id;

    std::string parseShader();
};


#endif //FRACTALS_SHADER_H
