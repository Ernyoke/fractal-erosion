#include "IndexBuffer.h"

#include <GL/glew.h>
#include "ErrorHandler.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : count{count}, renderer_id{0} {
    glCall(glGenBuffers(1, &renderer_id));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    glCall(glDeleteBuffers(1, &renderer_id));
}

void IndexBuffer::bind() const {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
}

void IndexBuffer::unBind() const {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}