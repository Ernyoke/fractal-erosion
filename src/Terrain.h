#ifndef FRACTALS_TERRAIN_H
#define FRACTALS_TERRAIN_H

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Material.h"

#include <memory>

#include <glm/glm.hpp>

class Terrain {
public:
    Terrain(const void *vertex_data, unsigned int vertex_data_size, const unsigned int *index_data,
            unsigned int count);

    Terrain(const Terrain &terrain) = delete;

    Terrain &operator=(const Terrain &terrain) = delete;

    virtual ~Terrain();

    void bind() const;

    [[nodiscard]] unsigned int getNumberOfVertices() const;

    [[nodiscard]] glm::mat4 getModelMatrix() const;

    void rotate(double x_change);

    [[nodiscard]] Material getMaterial() const;

private:
    std::unique_ptr<VertexArray> vertex_array;
    std::unique_ptr<VertexBuffer> vertex_buffer;
    std::unique_ptr<VertexBufferLayout> vertex_buffer_layout;
    std::unique_ptr<IndexBuffer> index_buffer;

    Material material;

    glm::mat4 model_matrix;

    float rotation_angle;
    float rotation_speed;
};


#endif //FRACTALS_TERRAIN_H
