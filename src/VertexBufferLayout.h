//
// Created by ervin on 22.12.2019.
//

#ifndef FRACTALS_VERTEXBUFFERLAYOUT_H
#define FRACTALS_VERTEXBUFFERLAYOUT_H

#include <vector>
#include <GL/glew.h>

#include "VertexBufferLayoutElement.h"

class VertexBufferLayout {
public:
    VertexBufferLayout();

    template<typename T>
    void push(unsigned int count) {
//        static_assert(false);
    }

    inline unsigned int getStride() const {
        return stride;
    }

    inline std::vector<VertexBufferLayoutElement> getElements() const {
        return elements;
    }

private:
    std::vector<VertexBufferLayoutElement> elements;
    unsigned int stride;
};


#endif //FRACTALS_VERTEXBUFFERLAYOUT_H
