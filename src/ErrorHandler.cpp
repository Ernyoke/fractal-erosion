#include "ErrorHandler.h"

#include <GL/glew.h>
#include <iostream>

void ErrorHandling::glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool ErrorHandling::glLogCall(const std::string &function, const std::string &file_name, unsigned int line) {
    while (unsigned int error = glGetError()) {
        std::cerr << "[OPENGL error - code 0x"
                  << std::hex << error
                  << " in file: " << file_name << ":"
                  << std::dec << line
                  << " in function " << function
                  << std::endl;
        return true;
    }
    return false;
}
