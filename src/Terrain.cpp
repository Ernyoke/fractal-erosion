#include "Terrain.h"

Terrain::Terrain() = default;

Terrain::~Terrain() = default;

void Terrain::initVertexArray() {
    vertex_array = std::make_unique<VertexArray>();
    vertex_array->bind();
}

void Terrain::initVertexBufferLayout() {
    vertex_buffer_layout = std::make_unique<VertexBufferLayout>();
    vertex_buffer_layout->push<float>(3);
    vertex_buffer_layout->push<float>(4);
}

void Terrain::initBuffers(const void *vertex_data, unsigned int vertex_data_size, const unsigned int *index_data,
                          unsigned int count) {
    vertex_buffer = std::make_unique<VertexBuffer>(vertex_data, vertex_data_size);
    index_buffer = std::make_unique<IndexBuffer>(index_data, count);
}

void Terrain::addBuffersToVertexArray() {
    vertex_array->addBuffer(vertex_buffer, vertex_buffer_layout);
}

void Terrain::bind() const {
    vertex_array->bind();
    index_buffer->bind();
}

unsigned int Terrain::getNumberOfVertices() const {
    return index_buffer->getCount();
}
