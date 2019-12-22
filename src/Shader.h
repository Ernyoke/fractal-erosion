#ifndef FRACTALS_SHADER_H
#define FRACTALS_SHADER_H

#include <iostream>

class Shader {
public:
    Shader(std::string path, unsigned int shader_type, unsigned int shader_program_id);

    void parseShader();

    void createShader();

    void bindShader();

    void unbindShader();

private:
    std::string path;
    unsigned int shader_type;
    std::string source;
    unsigned int shader_program_id;

    unsigned int compileShader();
};


#endif //FRACTALS_SHADER_H
