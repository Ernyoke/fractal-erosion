//
// Created by ervin on 22.12.2019.
//

#ifndef FRACTALS_VERTEXBUFFERLAYOUTELEMENT_H
#define FRACTALS_VERTEXBUFFERLAYOUTELEMENT_H

struct VertexBufferLayoutElement {
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    unsigned int getSizeOfType() const;
};


#endif //FRACTALS_VERTEXBUFFERLAYOUTELEMENT_H
