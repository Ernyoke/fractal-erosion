#ifndef FRACTALS_TEXTURE_H
#define FRACTALS_TEXTURE_H

#include <string>

class Texture {
public:
    explicit Texture(const std::string& path);

    Texture(const Texture &terrain) = delete;

    Texture &operator=(const Texture &terrain) = delete;

    virtual ~Texture();

    void bind(unsigned int slot = 0) const;

    void unBind();

private:
    unsigned int renderer_id;
    std::string path;
    unsigned char *local_buffer;
    int width;
    int height;
    int bpp;
};


#endif //FRACTALS_TEXTURE_H
