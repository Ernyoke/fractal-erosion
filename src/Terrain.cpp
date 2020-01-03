#include "Terrain.h"

#include <glm/gtc/matrix_transform.hpp>

Terrain::Terrain(const void *vertex_data, unsigned int vertex_data_size, const unsigned int *index_data,
                 unsigned int count, float rotation_angle) : model_matrix{1.0f},
                                                             rotation_angle{rotation_angle},
                                                             rotation_speed{0.01f},
                                                             material{0.5f, 32.0f} {
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

    // we expect that the layout for the normal is a vec4 of floats
    vertex_buffer_layout->push<float>(3);

    // attach the vertex buffer and
    vertex_array->addBuffer(vertex_buffer, vertex_buffer_layout);

    // applies rotation the the model matrix
    applyRotation();
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

    applyRotation();
}

glm::mat4 Terrain::getModelMatrix() const {
    return model_matrix;
}

Material Terrain::getMaterial() const {
    return material;
}

float Terrain::getRotationAngle() const {
    return rotation_angle;
}

void Terrain::applyRotation() {
    model_matrix = glm::rotate(glm::mat4{1.0f},
                               static_cast<float>(rotation_angle),
                               glm::vec3{0.0f, 1.0f, 0.0f});
}
