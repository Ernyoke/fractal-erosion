#include "Display.h"

#include <iostream>

Display::Display(int width, int height, std::string title) : width{width},
                                                             height{height},
                                                             title{std::move(title)},
                                                             is_closed{false},
                                                             window{nullptr},
                                                             clear_color{ImVec4(0.45f, 0.55f, 0.60f, 1.00f)},
                                                             show_demo_window{true},
                                                             show_another_window{false},
                                                             camera{nullptr},
                                                             keyboard_keys{false},
                                                             mouse_first_moved{true} {
}

Display::~Display() {
//    shutDownImgui();
    glfwTerminate();
}

int Display::initialize() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cerr << "OPENGL could not be initialized!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    initInputCallbacks();
//    initImgui();

    return 0;
}

void Display::addCamera(const std::shared_ptr<Camera> &camera) {
    this->camera = camera;
}

void Display::update() {
    if (glfwWindowShouldClose(window)) {
        is_closed = true;
        return;
    }
    handleInputs();
//    newFrameImgui();
//    renderImgui();
    glfwSwapBuffers(window);
    glfwPollEvents();
}

//void Display::handleKeyboardInput() {
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//        std::cout << "UP" << std::endl;
//        camera->moveForward(0.05f);
//    }
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//        std::cout << "DOWN" << std::endl;
//        camera->moveBackward(0.05f);
//    }
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//        std::cout << "LEFT" << std::endl;
//        camera->moveLeft(0.05f);
//    }
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//        std::cout << "RIGHT" << std::endl;
//        camera->moveRight(0.05f);
//    }
//}

void Display::initImgui() {
    const char *glsl_version = "#version 130";

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void Display::newFrameImgui() const {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Display::renderImgui() {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin(
            "Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float *) &clear_color); // Edit 3 floats representing a color

    if (ImGui::Button(
            "Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Display::shutDownImgui() const {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool Display::isClosed() const {
    return is_closed;
}

void Display::initInputCallbacks() {
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, handleKeyboardInput);
    glfwSetCursorPosCallback(window, handleMouseMovement);
    glfwSetMouseButtonCallback(window, handleMouseKeyInput);
}

void Display::handleInputs() {
    for (int key = 0; key < 1024; key++) {
        switch (key) {
            case GLFW_KEY_W: {
                if (keyboard_keys[key]) {
                    std::cout << "W PRESSED" << std::endl;
                }
                break;
            }
            case GLFW_KEY_S: {
                if (keyboard_keys[key]) {
                    std::cout << "S PRESSED" << std::endl;
                }
                break;
            }
            case GLFW_KEY_A: {
                if (keyboard_keys[key]) {
                    std::cout << "A PRESSED" << std::endl;
                }
                break;
            }
            case GLFW_KEY_D: {
                if (keyboard_keys[key]) {
                    std::cout << "D PRESSED" << std::endl;
                }
                break;
            }
            default: {
                // Do nothing
            }
        }
    }
}

void Display::handleKeyboardInput(GLFWwindow *window, int key, int code, int action, int mode) {
    auto *self = static_cast<Display *>(glfwGetWindowUserPointer(window));
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            self->keyboard_keys[key] = true;
        }
        if (action == GLFW_RELEASE) {
            self->keyboard_keys[key] = false;
        }
    }
}

void Display::handleMouseMovement(GLFWwindow *window, double x, double y) {
    auto *self = static_cast<Display *>(glfwGetWindowUserPointer(window));
    if (self->mouse_first_moved) {
        self->last_x = x;
        self->last_y = y;
        self->mouse_first_moved = false;
    } else {
        self->x_change = x - self->last_x;
        self->y_change = y - self->last_y;
        self->last_x = x;
        self->last_y = y;
    }
}

void Display::handleMouseKeyInput(GLFWwindow *window, int button, int action, int mode) {
    auto *self = static_cast<Display *>(glfwGetWindowUserPointer(window));
    if (button >= 0 && button < 8) {
        if (action == GLFW_PRESS) {
            self->mouse_buttons[button] = true;
        }
        if (action == GLFW_RELEASE) {
            self->mouse_buttons[button] = false;
        }
    }
}
