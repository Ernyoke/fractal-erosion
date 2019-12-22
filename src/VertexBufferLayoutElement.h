#ifndef FRACTALS_VERTEXBUFFERLAYOUTELEMENT_H
#define FRACTALS_VERTEXBUFFERLAYOUTELEMENT_H

struct VertexBufferLayoutElement {
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    [[nodiscard]] unsigned int getSizeOfType() const;
};


#endif //FRACTALS_VERTEXBUFFERLAYOUTELEMENT_H
