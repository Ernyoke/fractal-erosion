#include "Terrain.h"

#include <glm/gtc/matrix_transform.hpp>

Terrain::Terrain(const void *vertex_data, unsigned int vertex_data_size, const unsigned int *index_data,
                 unsigned int count) : model_matrix{1.0f}, rotation_angle{0.0f}, rotation_speed{0.01f} {
    // initialize vertex array
    vertex_array = std::make_unique<VertexArray>();
    vertex_array->bind();

    // initialize vertex and index buffers;
    vertex_buffer = std::make_unique<VertexBuffer>(vertex_data, vertex_data_size);
    index_buffer = std::make_unique<IndexBuffer>(index_data, count);

    // initialize the vertex buffer layout
    vertex_buffer_layout = std::make_unique<VertexBufferLayout>();

    // we expect that the layout for the vertex data is vec3 of floats for the indices
    vertex_buffer_layout->push<float>(3);

    // we expect that the layout for for the color information is vec4 with floats for RGBA channels
    vertex_buffer_layout->push<float>(4);

    // attach the vertex buffer and
    vertex_array->addBuffer(vertex_buffer, vertex_buffer_layout);
}

Terrain::~Terrain() = default;

void Terrain::bind() const {
    vertex_array->bind();
    index_buffer->bind();
}

unsigned int Terrain::getNumberOfVertices() const {
    return index_buffer->getCount();
}

void Terrain::rotate(double x_change) {
    rotation_angle += static_cast<float>(x_change) * rotation_speed;

    if (std::abs(rotation_angle) > 6.28) {
        rotation_angle = 0.0;
    }

    model_matrix = glm::rotate(glm::mat4{1.0f}, static_cast<float>(rotation_angle), glm::vec3{0.0f, 1.0f, 0.0f});
}

glm::mat4 Terrain::getModelMatrix() const {
    return model_matrix;
}
