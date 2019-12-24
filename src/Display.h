#ifndef FRACTALS_DISPLAY_H
#define FRACTALS_DISPLAY_H

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "libs/imgui/imgui.h"
#include "libs/imgui/imgui_impl_glfw.h"
#include "libs/imgui/imgui_impl_opengl3.h"

class Display {
public:
    Display(int width, int height, std::string title);

    Display(const Display &display) = delete;

    Display &operator=(const Display &display) = delete;

    virtual ~Display();

    int initialize();

    void update();

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

    void initImgui();

    void newFrameImgui() const;

    void renderImgui();

    void shutDownImgui() const;
};


#endif //FRACTALS_DISPLAY_H
