#ifndef FRACTALS_INDEXBUFFER_H
#define FRACTALS_INDEXBUFFER_H

class IndexBuffer {
public:
    IndexBuffer(const unsigned int *data, unsigned int count);

    IndexBuffer(const IndexBuffer &index_buffer) = delete;

    IndexBuffer &operator=(const IndexBuffer &index_buffer) = delete;

    virtual ~IndexBuffer();

    void bind() const;

    void unBind() const;

    inline unsigned int getCount() const {
        return count;
    }

private:
    unsigned int renderer_id;
    unsigned int count;
};


#endif //FRACTALS_INDEXBUFFER_H
