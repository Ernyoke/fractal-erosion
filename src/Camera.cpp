#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3 &position, const glm::vec3 &world_up, float yaw, float pitch)
        : position{position},
          front{0.0f, 0.0f, -1.0f},
          up{world_up},
          right{1.0f, 0.0f, 0.0f},
          yaw{yaw},
          pitch{pitch},
          world_up{world_up},
          movement_speed{1.0f},
          turn_speed{0.1f} {
    update();
}

void Camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, world_up));

    up = glm::normalize(glm::cross(right, front));
}

void Camera::move_forward(double delta_time) {
    position += front * movement_speed * static_cast<float>(delta_time);
}

void Camera::move_backward(double delta_time) {
    position -= front * movement_speed * static_cast<float>(delta_time);
}

void Camera::move_left(double delta_time) {
    position -= right * movement_speed * static_cast<float>(delta_time);
}

void Camera::move_right(double delta_time) {
    position += right * movement_speed * static_cast<float>(delta_time);
}

void Camera::turn(double x, double y) {
    float x_velocity = static_cast<float>(x) * turn_speed;
    float y_velocity = static_cast<float>(y) * turn_speed;

    yaw += x_velocity;
    pitch += y_velocity;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    update();
}

glm::mat4 Camera::calculateViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}
