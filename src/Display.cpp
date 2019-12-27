#include "Display.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

Display::Display(int width, int height, float field_of_view, std::string title)
        : width{width},
          height{height},
          title{std::move(title)},
          is_closed{false},
          projection_matrix{
                  glm::perspective(field_of_view,
                                   static_cast<float>(width) / static_cast<float>(height),
                                   Z_NEAR,
                                   Z_FAR)},
          window{nullptr},
          camera{
                  glm::vec3{0.0f, 10.0f, 1.0f},
                  glm::vec3{0.0f, 1.0f, 0.0f},
                  -90.0f,
                  0.0f},
          fractal{nullptr},
          delta_time{0.0},
          last_time{0.0},
          keyboard_keys{false},
          mouse_buttons{false},
          last_x{0.0},
          last_y{0.0},
          x_change{0.0},
          y_change{0.0},
          mouse_first_moved{true},
          clear_color{ImVec4{0.45f, 0.55f, 0.60f, 1.00f}},
          show_demo_window{true},
          show_another_window{false} {
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

    createFractal();
    initShaderProgram();

    return 0;
}

void Display::update() {
    if (glfwWindowShouldClose(window)) {
        is_closed = true;
        return;
    }

    double now = glfwGetTime();
    delta_time = now - last_time;
    last_time = now;

    renderer.clear();
    shader_program->setUniformMat4f("u_MVP", projection_matrix * camera.calculateViewMatrix());
    renderer.draw(terrain, shader_program);

    handleKeyboardInputs();
    camera.update();

//    newFrameImgui();
//    renderImgui();

    glfwSwapBuffers(window);
    glfwPollEvents();
}


bool Display::isClosed() const {
    return is_closed;
}

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

void Display::createFractal() {
    fractal = std::make_unique<DiamondSquareFractal>();
    fractal_result = fractal->generate();
    terrain.initVertexArray();
    terrain.initBuffers(fractal_result.vertices->data(), fractal_result.vertices->size() * Vertex::SIZE,
                        fractal_result.indices->data(), fractal_result.indices->size());
    terrain.initVertexBufferLayout();
    terrain.addBuffersToVertexArray();
}

void Display::initShaderProgram() {
    shader_program = std::make_unique<ShaderProgram>();

    Shader vertex_shader("./res/shaders/vertex.shader", GL_VERTEX_SHADER);
    vertex_shader.compileShader();
    vertex_shader.attachShader(shader_program);

    Shader fragment_shader("./res/shaders/fragment.shader", GL_FRAGMENT_SHADER);
    fragment_shader.compileShader();
    fragment_shader.attachShader(shader_program);

    shader_program->bind();
    shader_program->setUniformMat4f("u_MVP", projection_matrix * camera.calculateViewMatrix());
}


void Display::initInputCallbacks() {
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, handleKeyboardInputCallback);
    glfwSetCursorPosCallback(window, handleMouseMovementCallback);
    glfwSetMouseButtonCallback(window, handleMouseKeyInputCallback);
}

void Display::handleKeyboardInputs() {
    for (int key = 0; key < NUMBER_KEYBOARD_KEYS; key++) {
        if (keyboard_keys[key]) {
            switch (key) {
                case GLFW_KEY_W: {
                    camera.move_forward(delta_time);
                    break;
                }
                case GLFW_KEY_S: {
                    camera.move_backward(delta_time);
                    break;
                }
                case GLFW_KEY_A: {
                    camera.move_left(delta_time);
                    break;
                }
                case GLFW_KEY_D: {
                    camera.move_right(delta_time);
                    break;
                }
                default: {
                    // Do nothing
                }
            }

        }
    }
}

void Display::handleKeyboardInputCallback(GLFWwindow *window, int key, int code, int action, int mode) {
    auto *self = static_cast<Display *>(glfwGetWindowUserPointer(window));
    if (key >= 0 && key < NUMBER_KEYBOARD_KEYS) {
        if (action == GLFW_PRESS) {
            self->keyboard_keys[key] = true;
        }
        if (action == GLFW_RELEASE) {
            self->keyboard_keys[key] = false;
        }
    }
}

void Display::handleMouseMovementCallback(GLFWwindow *window, double x, double y) {
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
        self->handleMouseInputs();
    }
}

void Display::handleMouseInputs() {
    for (int button = 0; button < NUMBER_MOUSE_BUTTONS; button++) {
        if (mouse_buttons[button]) {
            switch (button) {
                case GLFW_MOUSE_BUTTON_RIGHT:
                case GLFW_MOUSE_BUTTON_LEFT: {
                    camera.turn(x_change, y_change);
                    break;
                }
                default: {
                    // Do nothing
                }
            }
        }
    }
}

void Display::handleMouseKeyInputCallback(GLFWwindow *window, int button, int action, int mode) {
    auto *self = static_cast<Display *>(glfwGetWindowUserPointer(window));
    if (button >= 0 && button < NUMBER_MOUSE_BUTTONS) {
        if (action == GLFW_PRESS) {
            self->mouse_buttons[button] = true;
        }
        if (action == GLFW_RELEASE) {
            self->mouse_buttons[button] = false;
        }
    }
}