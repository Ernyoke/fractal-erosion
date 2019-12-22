//
// Created by ervin on 22.12.2019.
//

#include "VertexBuffer.h"

#include <GL/glew.h>
#include "ErrorHandler.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    glCall(glGenBuffers(1, &renderer_id));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    glCall(glDeleteBuffers(1, &renderer_id));
}

void VertexBuffer::bind() const {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
}

void VertexBuffer::unBind() const {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
