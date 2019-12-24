#include "ShaderProgram.h"

#include <iostream>

#include <GL/glew.h>

#include "ErrorHandler.h"

ShaderProgram::ShaderProgram() : program_id{0} {
    program_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glCall(glDeleteProgram(program_id));
}

void ShaderProgram::bind() const {
    glCall(glUseProgram(program_id));
}

void ShaderProgram::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    glCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void ShaderProgram::setUniform1i(const std::string &name, int value) {
    glCall(glUniform1i(getUniformLocation(name), value));
}

void ShaderProgram::setUniform1f(const std::string &name, float value) {
    glCall(glUniform1f(getUniformLocation(name), value));
}

void ShaderProgram::setUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
    glCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

unsigned int ShaderProgram::getUniformLocation(const std::string &name) {
    if (uniform_location_cache.contains(name)) {
        return uniform_location_cache[name];
    }
    int location = glGetUniformLocation(program_id, name.c_str());
    if (location < 0) {
        std::cerr << "Warning: Location " << name << " not found!" << std::endl;
    } else {
        uniform_location_cache.insert(std::pair<std::string, int>(name, location));
    }
    return location;
}

void ShaderProgram::update(Camera &camera) {

}
