#include <bits/unique_ptr.h>
#include "VertexArray.h"

#include "ErrorHandler.h"

VertexArray::VertexArray() : renderer_id{0} {
    glCall(glGenVertexArrays(1, &renderer_id));
}

VertexArray::~VertexArray() {
    glCall(glDeleteVertexArrays(1, &renderer_id));
}

void VertexArray::addBuffer(const std::unique_ptr<VertexBuffer> &vertex_buffer,
                            const std::unique_ptr<VertexBufferLayout> &vertex_buffer_layout) {
    vertex_buffer->bind();
    unsigned int offset = 0;
    const auto &elements = vertex_buffer_layout->getElements();
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto &element = elements[i];
        glCall(glEnableVertexAttribArray(i));
        glCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                     vertex_buffer_layout->getStride(), (const void *) offset));
        offset += element.count * element.getSizeOfType();
    }
}

void VertexArray::bind() const {
    glCall(glBindVertexArray(renderer_id));
}

void VertexArray::unBind() const {
    glCall(glBindVertexArray(0));
}
