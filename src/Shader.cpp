#include "Shader.h"

#include "ErrorHandler.h"

#include <string>
#include <sstream>
#include <utility>

#include <GL/glew.h>

Shader::Shader(std::string source, unsigned int shader_type)
        : source{std::move(source)},
          shader_type{shader_type},
          renderer_id{0} {
}

void Shader::compileShader() {
    renderer_id = glCreateShader(shader_type);
    const char *src = source.c_str();
    glCall(glShaderSource(renderer_id, 1, &src, nullptr))
    glCall(glCompileShader(renderer_id));
    int result;
    glCall(glGetShaderiv(renderer_id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        glCall(glGetShaderiv(renderer_id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *) alloca(length * sizeof(char));
        glCall(glGetShaderInfoLog(renderer_id, length, &length, message));
        std::cerr << "Failed to compile shader!" << std::endl;
        std::cerr << "Error: " << message << std::endl;
    }
}

void Shader::attachShader(const std::unique_ptr<ShaderProgram> &shaderProgram) const {
    unsigned int shader_program_id = shaderProgram->getProgramId();

    if (renderer_id) {
        glCall(glAttachShader(shader_program_id, renderer_id));
        glCall(glLinkProgram(shader_program_id));
        glCall(glValidateProgram(shader_program_id));
    }
}
