//
// Created by ervin on 22.12.2019.
//

#include "Shader.h"

#include <fstream>
#include <string>
#include <sstream>
#include <utility>

#include <GL/glew.h>

Shader::Shader(std::string path, unsigned int shader_type, unsigned int shader_program_id)
        : path{std::move(path)},
          shader_type{shader_type},
          shader_program_id{shader_program_id} {
}

void Shader::parseShader() {
    std::ifstream stream(path);

    std::string line;
    std::stringstream string_stream;
    while (getline(stream, line)) {
        string_stream << line << std::endl;
    }
    source = string_stream.str();
}

unsigned int Shader::compileShader() {
    unsigned int shader_id = glCreateShader(shader_type);
    const char *src = source.c_str();
    glShaderSource(shader_id, 1, &src, nullptr);
    glCompileShader(shader_id);
    int result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(shader_id, length, &length, message);
        std::cerr << "Failed to compile shader!" << std::endl;
        std::cerr << "Error: " << message << std::endl;
        return 0;
    }

    return shader_id;
}

void Shader::createShader() {
    unsigned int shader = compileShader();;

    if (shader) {
        glAttachShader(shader_program_id, shader);
        glLinkProgram(shader_program_id);
        glValidateProgram(shader_program_id);
    }
}

void Shader::bindShader() {
    glUseProgram(shader_program_id);
}

void Shader::unbindShader() {
    glUseProgram(0);
}
