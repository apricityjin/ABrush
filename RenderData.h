//
// Created by apricity on 2023/6/15.
//

#ifndef ABRUSH_RENDERDATA_H
#define ABRUSH_RENDERDATA_H

#include "Texture.h"
#include <iostream>

class RenderData
{

    struct Vertex
    {
        float x, y;
        float u, v;
    };

    RenderData(const std::vector<Vertex> &vertices, const std::vector<u_int32_t> &indices)
            : vertices(vertices), indices(indices)
    {}

    std::vector<Vertex>   vertices;
    std::vector<uint32_t> indices;
};


#endif //ABRUSH_RENDERDATA_H
