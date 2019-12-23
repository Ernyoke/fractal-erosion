#include "Shader.h"
#include "ErrorHandler.h"

#include <fstream>
#include <string>
#include <sstream>
#include <utility>

#include <GL/glew.h>

Shader::Shader(std::string path, unsigned int shader_type)
        : path{std::move(path)},
          shader_type{shader_type} {
}

Shader::~Shader() {
    glCall(glDeleteProgram(renderer_id))
}

std::string Shader::parseShader() {
    std::ifstream stream(path);

    std::string line;
    std::stringstream string_stream;
    while (getline(stream, line)) {
        string_stream << line << std::endl;
    }
    return string_stream.str();
}

void Shader::compileShader() {
    std::string source = parseShader();
    renderer_id = glCreateShader(shader_type);
    const char *src = source.c_str();
    glShaderSource(renderer_id, 1, &src, nullptr);
    glCompileShader(renderer_id);
    int result;
    glGetShaderiv(renderer_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(renderer_id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(renderer_id, length, &length, message);
        std::cerr << "Failed to compile shader!" << std::endl;
        std::cerr << "Error: " << message << std::endl;
    }
}

void Shader::attachShader(const ShaderProgram &shaderProgram) {
    unsigned int shader_program_id = shaderProgram.getProgramId();

    if (renderer_id) {
        glAttachShader(shader_program_id, renderer_id);
        glLinkProgram(shader_program_id);
        glValidateProgram(shader_program_id);
    }
}
