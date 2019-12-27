#ifndef FRACTALS_TERRAIN_H
#define FRACTALS_TERRAIN_H

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

#include <memory>

class Terrain {
public:
    Terrain();

    virtual ~Terrain();

    void initVertexArray();

    void initVertexBufferLayout();

    void initBuffers(const void *vertex_data, unsigned int vertex_data_size, const unsigned int *index_data,
                     unsigned int count);

    void addBuffersToVertexArray();

    void bind() const;

    [[nodiscard]] unsigned int getNumberOfVertices() const;

private:
    std::unique_ptr<VertexArray> vertex_array;
    std::unique_ptr<VertexBuffer> vertex_buffer;
    std::unique_ptr<VertexBufferLayout> vertex_buffer_layout;
    std::unique_ptr<IndexBuffer> index_buffer;
};


#endif //FRACTALS_TERRAIN_H
