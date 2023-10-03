#ifndef FRACTALS_RENDERER_H
#define FRACTALS_RENDERER_H

#include "Terrain.h"
#include "ShaderProgram.h"

class Renderer {
public:
    Renderer();

    Renderer(const Renderer &renderer) = delete;

    Renderer &operator=(const Renderer &renderer) = delete;

    virtual ~Renderer();

    static void clear() ;

    static void draw(const std::unique_ptr<Terrain> &terrain, const std::unique_ptr<ShaderProgram> &shader_program) ;
};


#endif //FRACTALS_RENDERER_H
