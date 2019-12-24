#include "Transform.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>

Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
        : position{position}, rotation{rotation}, scale{scale} {
}

glm::mat4 Transform::getModel() const {
    glm::mat4 position_matrix = glm::translate(position);
    glm::mat4 rotation_x_matrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
    glm::mat4 rotation_y_matrix = glm::rotate(rotation.x, glm::vec3(0, 1, 0));
    glm::mat4 rotation_z_matrix = glm::rotate(rotation.x, glm::vec3(0, 0, 1));
    glm::mat4 rotation_matrix = rotation_z_matrix * rotation_y_matrix * rotation_x_matrix;
    glm::mat4 scale_matrix = glm::scale(scale);

    return scale_matrix * rotation_matrix * scale_matrix;
}
