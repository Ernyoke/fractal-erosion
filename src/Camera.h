#ifndef FRACTALS_CAMERA_H
#define FRACTALS_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera(const glm::vec3 &position, const glm::vec3 &world_up, float yaw, float pitch);

    virtual ~Camera() = default;

    void update();

    void move_forward(double delta_time);

    void move_backward(double delta_time);

    void move_left(double delta_time);

    void move_right(double delta_time);

    void turn(double x, double y);

    [[nodiscard]] glm::mat4 calculateViewMatrix() const;


private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    float yaw;
    float pitch;

    float movement_speed;
    float turn_speed;

};


#endif //FRACTALS_CAMERA_H
