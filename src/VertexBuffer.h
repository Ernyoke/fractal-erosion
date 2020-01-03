#ifndef FRACTALS_VERTEXBUFFER_H
#define FRACTALS_VERTEXBUFFER_H

class VertexBuffer {
public:
    VertexBuffer(const void *data, unsigned int size);

    VertexBuffer(const VertexBuffer &vertex_buffer) = delete;

    VertexBuffer &operator=(const VertexBuffer &vertex_buffer) = delete;

    virtual ~VertexBuffer();

    void bind() const;

    void unBind() const;

private:
    unsigned int renderer_id;
};


#endif //FRACTALS_VERTEXBUFFER_H
