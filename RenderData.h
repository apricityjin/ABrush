//
// Created by apricity on 2023/6/15.
//

#ifndef ABRUSH_RENDERDATA_H
#define ABRUSH_RENDERDATA_H

#include <iostream>

struct RenderData
{

    struct Vertex
    {
        float x, y;
        float u, v;
    };

    RenderData(const std::vector<Vertex> &vertices, const std::vector<uint16_t> &indices)
            : vertices(vertices), indices(indices)
    {}

    RenderData()
    =default;

    // 每条线段都有offset，从0开始
    std::vector<uint> vertex_offsets;
    std::vector<uint> index_offsets;
    // element 总数、 vertex 总数
    uint index_count;
    uint vertex_count;
    // 直接将所有的vertices和indices往这两个vector塞
    std::vector<Vertex>   vertices;
    std::vector<uint16_t> indices;
};


#endif //ABRUSH_RENDERDATA_H
