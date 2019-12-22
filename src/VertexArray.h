#ifndef FRACTALS_VERTEXARRAY_H
#define FRACTALS_VERTEXARRAY_H


#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
public:
    VertexArray();

    virtual ~VertexArray();

    void addBuffer(const VertexBuffer &vertex_buffer, const VertexBufferLayout &vertex_buffer_layout);

    void bind() const;

    void unBind() const;

private:
    unsigned int renderer_id;
};


#endif //FRACTALS_VERTEXARRAY_H
