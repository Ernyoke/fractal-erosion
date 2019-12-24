#ifndef FRACTALS_TRANSFORM_H
#define FRACTALS_TRANSFORM_H

#include <glm/glm.hpp>

class Transform {
public:
    Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale = {1.0f, 1.0f, 1.0f});

    virtual ~Transform() = default;

    [[nodiscard]] inline glm::vec3 getPosition() const {
        return position;
    }

    [[nodiscard]] inline glm::vec3 getRotation() const {
        return rotation;
    }

    [[nodiscard]] inline glm::vec3 getScale() const {
        return scale;
    }

    [[nodiscard]] glm::mat4 getModel() const;

private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};


#endif //FRACTALS_TRANSFORM_H
