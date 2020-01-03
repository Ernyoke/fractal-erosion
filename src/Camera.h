#ifndef FRACTALS_CAMERA_H
#define FRACTALS_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera(const glm::vec3 &position, const glm::vec3 &world_up, float yaw, float pitch);

    Camera(const Camera &display) = delete;

    Camera &operator=(const Camera &display) = delete;

    virtual ~Camera() = default;

    void update();

    void move_forward(double delta_time, float movement_speed = 10.0f);

    void move_backward(double delta_time, float movement_speed = 10.0f);

    void move_left(double delta_time, float movement_speed = 10.0f);

    void move_right(double delta_time, float movement_speed = 10.0f);

    void turn(double x, double y);

    [[nodiscard]] glm::mat4 calculateViewMatrix() const;

    [[nodiscard]] glm::vec3 getPosition() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    float yaw;
    float pitch;

    float turn_speed;

};


#endif //FRACTALS_CAMERA_H
