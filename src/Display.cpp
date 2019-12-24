#include "Display.h"

#include <iostream>

Display::Display(int width, int height, std::string title) : width{width},
                                                             height{height},
                                                             title{std::move(title)},
                                                             is_closed{false},
                                                             window{nullptr},
                                                             clear_color{ImVec4(0.45f, 0.55f, 0.60f, 1.00f)},
                                                             show_demo_window{true},
                                                             show_another_window{false} {
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

    initImgui();

    return 0;
}

void Display::update() {
    if (glfwWindowShouldClose(window)) {
        is_closed = true;
    }
    newFrameImgui();
    renderImgui();
    glfwSwapBuffers(window);
    glfwPollEvents();
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

bool Display::isClosed() const {
    return is_closed;
}
