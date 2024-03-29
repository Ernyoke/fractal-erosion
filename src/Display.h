#ifndef FRACTALS_DISPLAY_H
#define FRACTALS_DISPLAY_H

#include <string>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Camera.h"
#include "DiamondSquareFractal.h"
#include "Terrain.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Light.h"

constexpr int NUMBER_KEYBOARD_KEYS = 1024;
constexpr int NUMBER_MOUSE_BUTTONS = 8;
constexpr float Z_NEAR = 0.1f;
constexpr float Z_FAR = 500.0f;

class Display {
public:
    Display(int width, int height, float field_of_view, std::string title);

    Display(const Display &display) = delete;

    Display &operator=(const Display &display) = delete;

    virtual ~Display();

    int initialize();

    void update();

    [[nodiscard]] bool isClosed() const;

private:
    int width;
    int height;
    float field_of_view;
    std::string title;
    bool is_closed;

    glm::mat4 projection_matrix;

    GLFWwindow *window;
    Camera camera;
    std::unique_ptr<Terrain> terrain;
    std::unique_ptr<ShaderProgram> shader_program;
    Light directional_light;

    std::unique_ptr<DiamondSquareFractal> fractal;

    double delta_time;
    double last_time_stamp;

    float roughness;
    int grid_size;
    int seed;

    int thermal_erosion_iterations;

    int hydraulic_erosion_iteration;
    float water_quantity;

    ImVec4 clear_color;

    bool keyboard_keys[1024];
    bool mouse_buttons[8];

    double last_x;
    double last_y;
    double x_change;
    double y_change;
    bool mouse_first_moved;

    // opengl
    void loadTerrain();

    void initShaderProgram();

    // glfw initialize callbacks
    void initCallbacks();

    // user input
    void handleKeyboardInputs();

    void handleMouseInputs();

    static void handleKeyboardInputCallback(GLFWwindow *window, int key, int code, int action, int mode);

    static void handleMouseMovementCallback(GLFWwindow *window, double x, double y);

    static void handleMouseKeyInputCallback(GLFWwindow *window, int button, int action, int mode);

    static void handleMouseScrollInputCallback(GLFWwindow *window, double x, double y);

    // window size
    static void handleWindowSizeCallback(GLFWwindow *window, int width, int height);

    static glm::mat4 calcProjectionMatrix(int width, int height, float field_of_view);

    // imgui
    void initImgui();

    static void newFrameImgui() ;

    void renderImgui();

    void imguiGenerateTerrainGroup();

    void imguiApplyTermalErrosionGroup();

    void imguiApplyHydraulicErosionGroup();

    static void shutDownImgui() ;
};


#endif //FRACTALS_DISPLAY_H
