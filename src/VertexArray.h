#ifndef FRACTALS_VERTEXARRAY_H
#define FRACTALS_VERTEXARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>

class VertexArray {
public:
    VertexArray();

    VertexArray(const VertexArray &vertex_array) = delete;

    VertexArray &operator=(const VertexArray &vertex_array) = delete;

    virtual ~VertexArray();

    void
    addBuffer(const std::unique_ptr<VertexBuffer> &vertex_buffer,
              const std::unique_ptr<VertexBufferLayout> &vertex_buffer_layout);

    void bind() const;

    void unBind() const;

private:
    unsigned int renderer_id;
};


#endif //FRACTALS_VERTEXARRAY_H
