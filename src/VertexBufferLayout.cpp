//
// Created by ervin on 22.12.2019.
//

#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout() : stride{0} {
}

template<>
void VertexBufferLayout::push<float>(unsigned int count) {
    VertexBufferLayoutElement element = {GL_FLOAT, count, GL_FALSE};
    elements.push_back(element);
    stride += element.getSizeOfType() * count;
}

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count) {
    VertexBufferLayoutElement element = {GL_UNSIGNED_INT, count, GL_FALSE};
    elements.push_back(element);
    stride += element.getSizeOfType() * count;
}

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count) {
    VertexBufferLayoutElement element = {GL_UNSIGNED_BYTE, count, GL_TRUE};
    elements.push_back(element);
    stride += element.getSizeOfType() * count;
}