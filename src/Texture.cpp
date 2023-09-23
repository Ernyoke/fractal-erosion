#include "Texture.h"

#include "ErrorHandler.h"
#include "stb_image.h"

#include <GL/glew.h>

Texture::Texture(std::string path) : path{path},
                                     local_buffer{nullptr},
                                     width{0},
                                     height{0},
                                     bpp{0},
                                     renderer_id{0} {
    stbi_set_flip_vertically_on_load(1);
    local_buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

    glCall(glGenTextures(1, &renderer_id));
    glCall(glBindTexture(GL_TEXTURE_2D, renderer_id));

    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer));
    glCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (local_buffer) {
        stbi_image_free(local_buffer);
    }
}

Texture::~Texture() {
    glCall(glDeleteTextures(1, &renderer_id));
}

void Texture::bind(unsigned int slot) const {
    glCall(glActiveTexture(GL_TEXTURE0 + slot));
    glCall(glBindTexture(GL_TEXTURE_2D, renderer_id));
}

void Texture::unBind() {
    glCall(glBindTexture(GL_TEXTURE_2D, 0));
}
