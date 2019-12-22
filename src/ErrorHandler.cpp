//
// Created by ervin on 22.12.2019.
//

#include "ErrorHandler.h"

#include <GL/glew.h>
#include <iostream>

void ErrorHandling::glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool ErrorHandling::glLogCall(std::string function, std::string file_name, unsigned int line) {
    while (unsigned int error = glGetError()) {
        std::cerr << "[OPENGL error - code 0x"
                  << std::hex << error
                  << " in file " << file_name << ":"
                  << std::dec << line << std::endl;
        return true;
    }
    return false;
}
