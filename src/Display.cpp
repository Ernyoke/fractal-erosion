#include "Display.h"
#include "Material.h"

#include <iostream>
#include <future>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

Display::Display(int width, int height, float field_of_view, std::string title)
        : width{width},
          height{height},
          field_of_view{field_of_view},
          title{std::move(title)},
          is_closed{false},
          projection_matrix{calcProjectionMatrix(width, height, field_of_view)},
          window{nullptr},
          camera{
                  glm::vec3{0.0f, 25.0f, 45.0f},
                  glm::vec3{0.0f, 1.0f, 0.0f},
                  -90.0f,
                  -35.0f},
          terrain{nullptr},
          directional_light{
                  glm::vec3{1.0f},
                  0.5f,
                  glm::vec3{2.0f, -2.0f, -2.0f},
                  0.7f},
          fractal{std::make_unique<DiamondSquareFractal>()},
          delta_time{0.0},
          last_time_stamp{0.0},
          keyboard_keys{false},
          mouse_buttons{false},
          last_x{0.0},
          last_y{0.0},
          x_change{0.0},
          y_change{0.0},
          mouse_first_moved{true},
          clear_color{ImVec4{0.45f, 0.55f, 0.60f, 1.00f}},
          roughness{5.0f},
          grid_size{7},
          seed{25},
          thermal_erosion_iterations{10},
          hydraulic_erosion_iteration{10},
          water_quantity{0.1} {
}

Display::~Display() {
    shutDownImgui();
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

    initCallbacks();
    initImgui();

//    auto future = std::async(std::launch::async, &Display::createFractal, this);
//    future.get();
    createFractal();
    initShaderProgram();

    return 0;
}

void Display::update() {
    if (glfwWindowShouldClose(window)) {
        is_closed = true;
        return;
    }
    directional_light.useLight(shader_program);
    terrain->getMaterial().useMaterial(shader_program);

    double now = glfwGetTime();
    delta_time = now - last_time_stamp;
    last_time_stamp = now;

    renderer.clear();
    shader_program->setUniformMat4f("u_Model", terrain->getModelMatrix());
    shader_program->setUniformMat4f("u_View", camera.calculateViewMatrix());
    shader_program->setUniformMat4f("u_Projection", projection_matrix);
    shader_program->setUniform3f("u_EyePosition", camera.getPosition());
    renderer.draw(terrain, shader_program);

    handleKeyboardInputs();
    camera.update();

    newFrameImgui();
    renderImgui();

    glfwSwapBuffers(window);
    glfwPollEvents();
}


bool Display::isClosed() const {
    return is_closed;
}

void Display::initImgui() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Display::newFrameImgui() const {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Display::renderImgui() {
    bool wireframe = false;

    ImGui::Begin("Fractal Erosion");

    ImGui::Checkbox("Wireframe", &wireframe);

    ImGui::Separator();

    ImGui::BeginGroup();
    ImGui::Text("Diamond Square");
    ImGui::SliderFloat("Roughness", &roughness, 0.0f, 10.0f);
    ImGui::SliderInt("Grid size", &grid_size, 2, 8);
    ImGui::SliderInt("Seed", &seed, 1, 100);
    if (ImGui::Button("Generate")) {
        createFractal();
    }
    ImGui::EndGroup();

    ImGui::Separator();

    ImGui::BeginGroup();
    ImGui::Text("Thermal Erosion");
    ImGui::InputInt("Iterations", &thermal_erosion_iterations, 1, 100);
    if (ImGui::Button("Apply Thermal Erosion")) {
        for (int i = 0; i < thermal_erosion_iterations; i++) {
            fractal->applyThermalErosion();
        }
        Mesh mesh = fractal->generateMesh();
        terrain = std::make_unique<Terrain>(mesh.vertices->data(),
                                            mesh.vertices->size() * Vertex::SIZE,
                                            mesh.indices->data(),
                                            mesh.indices->size());
    }
    ImGui::EndGroup();

    ImGui::Separator();

    ImGui::BeginGroup();
    ImGui::Text("Hydraulic Erosion");
    ImGui::InputInt("Iterations", &hydraulic_erosion_iteration, 1, 100);
    ImGui::InputFloat("Water Quantity", &water_quantity, 0.1f, 1.0f);
    if (ImGui::Button("Apply Hydraulic Erosion")) {
        for (int i = 0; i < hydraulic_erosion_iteration; i++) {
            fractal->applyHydraulicErosion(water_quantity, 0.5f);
        }
        Mesh mesh = fractal->generateMesh();
        terrain = std::make_unique<Terrain>(mesh.vertices->data(),
                                            mesh.vertices->size() * Vertex::SIZE,
                                            mesh.indices->data(),
                                            mesh.indices->size());
    }
    ImGui::EndGroup();

    ImGui::Separator();

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
    fractal->generateGrid(static_cast<int>(std::pow(2, grid_size)) + 1, seed, roughness / 5.0f);
    Mesh mesh = fractal->generateMesh();
    terrain = std::make_unique<Terrain>(mesh.vertices->data(),
                                        mesh.vertices->size() * Vertex::SIZE,
                                        mesh.indices->data(),
                                        mesh.indices->size());
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
}


void Display::initCallbacks() {
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, handleKeyboardInputCallback);
    glfwSetCursorPosCallback(window, handleMouseMovementCallback);
    glfwSetMouseButtonCallback(window, handleMouseKeyInputCallback);
    glfwSetScrollCallback(window, handleMouseScrollInputCallback);
    glfwSetWindowSizeCallback(window, handleWindowSizeCallback);
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
    if (!ImGui::IsAnyWindowFocused()) {
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
    if (!ImGui::IsAnyWindowFocused()) {
        for (int button = 0; button < NUMBER_MOUSE_BUTTONS; button++) {
            if (mouse_buttons[button]) {
                switch (button) {
                    case GLFW_MOUSE_BUTTON_RIGHT:
                    case GLFW_MOUSE_BUTTON_LEFT: {
                        camera.turn(0.0f, y_change);
                        terrain->rotate(x_change);
                        break;
                    }
                    default: {
                        // Do nothing
                    }
                }
            }
        }
    }
}

void Display::handleMouseKeyInputCallback(GLFWwindow *window, int button, int action, int mode) {
    if (!ImGui::IsAnyWindowFocused()) {
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
}

void Display::handleMouseScrollInputCallback(GLFWwindow *window, double x, double y) {
    if (!ImGui::IsAnyWindowFocused()) {
        auto *self = static_cast<Display *>(glfwGetWindowUserPointer(window));
        if (y > 0) {
            self->camera.move_forward(self->delta_time);
        } else {
            if (y < 0) {
                self->camera.move_backward(self->delta_time);
            }
        }
    }
}

void Display::handleWindowSizeCallback(GLFWwindow *window, int width, int height) {
    auto *self = static_cast<Display *>(glfwGetWindowUserPointer(window));
    self->width = width;
    self->height = height;
    self->projection_matrix = calcProjectionMatrix(width, height, self->field_of_view);
    glViewport(0, 0, width, height);
}

glm::mat4 Display::calcProjectionMatrix(int width, int height, float field_of_view) {
    return glm::perspective(field_of_view,
                            static_cast<float>(width) / static_cast<float>(height),
                            Z_NEAR,
                            Z_FAR);
}
