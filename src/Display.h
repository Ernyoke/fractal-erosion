#ifndef FRACTALS_DISPLAY_H
#define FRACTALS_DISPLAY_H

#include <string>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "libs/imgui/imgui.h"
#include "libs/imgui/imgui_impl_glfw.h"
#include "libs/imgui/imgui_impl_opengl3.h"

#include "Camera.h"

class Display {
public:
    Display(int width, int height, std::string title);

    Display(const Display &display) = delete;

    Display &operator=(const Display &display) = delete;

    virtual ~Display();

    int initialize();

    void update();

    void addCamera(const std::shared_ptr<Camera> &camera);

    [[nodiscard]] bool isClosed() const;

private:
    int width;
    int height;
    std::string title;
    bool is_closed;

    bool show_demo_window;
    bool show_another_window;
    ImVec4 clear_color;

    GLFWwindow *window;

    std::shared_ptr<Camera> camera;

    void initImgui();

    void newFrameImgui() const;

    void renderImgui();

    void shutDownImgui() const;

    // user input
    bool keyboard_keys[1024];
    bool mouse_buttons[8];

    double last_x;
    double last_y;
    double x_change;
    double y_change;
    bool mouse_first_moved;

    void initInputCallbacks();

    void handleInputs();

    static void handleKeyboardInput(GLFWwindow *window, int key, int code, int action, int mode);

    static void handleMouseMovement(GLFWwindow *window, double x, double y);

    static void handleMouseKeyInput(GLFWwindow *window, int button, int action, int mode);
};


#endif //FRACTALS_DISPLAY_H
