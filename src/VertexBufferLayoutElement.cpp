//
// Created by ervin on 22.12.2019.
//

#include "VertexBufferLayoutElement.h"

#include <GL/glew.h>

unsigned int VertexBufferLayoutElement::getSizeOfType() const {
    switch (type) {
        case GL_FLOAT: {
            return 4;
        }
        case GL_UNSIGNED_BYTE: {
            return 1;
        }
        case GL_UNSIGNED_INT: {
            return 4;
        }
        default: {
            return 0;
        }
    }
}
