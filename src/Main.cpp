#include "Display.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr float FIELD_OF_VIEW = 70.0f;
const char *TITLE = "Fractals";

int main() {
    Display display(WIDTH, HEIGHT, FIELD_OF_VIEW, TITLE);
    if (display.initialize() < 0) {
        return -1;
    }

    while (!display.isClosed()) {
        display.update();
    }

    return 0;
}