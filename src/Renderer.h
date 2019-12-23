#ifndef FRACTALS_RENDERER_H
#define FRACTALS_RENDERER_H

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

class Renderer {
public:
    Renderer();

    virtual ~Renderer();

    void clear() const;

    void
    draw(const VertexArray &vertex_array, const IndexBuffer &index_buffer, const ShaderProgram &shader_program) const;
};


#endif //FRACTALS_RENDERER_H
