#include "ShaderProgram.h"

#include <GL/glew.h>

#include "ErrorHandler.h"

ShaderProgram::ShaderProgram() : program_id{0} {
    program_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glCall(glDeleteProgram(program_id));
}

void ShaderProgram::useShaderProgram() const {
    glCall(glUseProgram(program_id));
}
