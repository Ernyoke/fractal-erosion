#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3 &position, float field_of_view, float aspect_ratio, float z_near, float z_far)
        : position{position} {
    perspective = glm::perspective(field_of_view, aspect_ratio, z_near, z_far);
    forward = glm::vec3{0, 0, 1};
    up = glm::vec3{0, 1, 0};
}

glm::mat4 Camera::getViewProjection() const {
    return perspective * glm::lookAt(position, position + forward, up);
}
