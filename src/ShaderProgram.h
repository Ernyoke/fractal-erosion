#ifndef FRACTALS_SHADERPROGRAM_H
#define FRACTALS_SHADERPROGRAM_H

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include "Camera.h"

class ShaderProgram {
public:
    ShaderProgram();

    virtual ~ShaderProgram();

    [[nodiscard]] inline unsigned int getProgramId() const {
        return program_id;
    }

    void bind() const;

    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

    void setUniform1i(const std::string &name, int value);

    void setUniform1f(const std::string &name, float value);

    void setUniformMat4f(const std::string &name, const glm::mat4 &matrix);

    void update(Camera &camera);

private:
    unsigned int program_id;
    std::unordered_map<std::string, int> uniform_location_cache;

    unsigned int getUniformLocation(const std::string &name);
};


#endif //FRACTALS_SHADERPROGRAM_H
