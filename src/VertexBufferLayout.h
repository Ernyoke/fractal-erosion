#ifndef FRACTALS_VERTEXBUFFERLAYOUT_H
#define FRACTALS_VERTEXBUFFERLAYOUT_H

#include <vector>
#include <GL/glew.h>

#include "VertexBufferLayoutElement.h"

class VertexBufferLayout {
public:
    VertexBufferLayout();

    VertexBufferLayout(const VertexBufferLayout &vertex_buffer_layout) = delete;

    VertexBufferLayout &operator=(const VertexBufferLayout &vertex_buffer_layout) = delete;

    virtual ~VertexBufferLayout();

    template<typename T>
    void push(unsigned int count);

    [[nodiscard]] inline unsigned int getStride() const {
        return stride;
    }

    [[nodiscard]] inline std::vector<VertexBufferLayoutElement> getElements() const {
        return elements;
    }

private:
    std::vector<VertexBufferLayoutElement> elements;
    unsigned int stride;
};


#endif //FRACTALS_VERTEXBUFFERLAYOUT_H
