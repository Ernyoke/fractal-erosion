#ifndef FRACTALS_CAMERA_H
#define FRACTALS_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera(const glm::vec3 &position, float field_of_view, float aspect_ratio, float z_near, float z_far);

    virtual ~Camera() = default;

    [[nodiscard]] glm::mat4 getViewProjection() const;

    void moveForward(float d);

    void moveBackward(float d);

    void moveLeft(float d);

    void moveRight(float d);

private:
    glm::vec3 position;
    glm::mat4 perspective;
    glm::vec3 forward;
    glm::vec3 up;
};


#endif //FRACTALS_CAMERA_H
