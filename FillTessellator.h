//
// Created by apricity on 2023/6/13.
//

#ifndef ABRUSH_FILLTESSELLATOR_H
#define ABRUSH_FILLTESSELLATOR_H

#include <iostream>
#include "Path.h"
#include "libtess2/Include/tesselator.h"
#include "RenderData.h"

namespace ABrush
{
    class FillTessellator
    {
    public:
        RenderData fill(Flatten *flattens)
        {
            RenderData data = RenderData();
            size_t size = flattens[0].size;
            uint vertex_offset = 0; // 顶点的偏移，只用在设置 indices 的时候添加
            uint index_offset = 0;
            for (size_t i = 0; i < size; ++i) {
                auto f = flattens[i];
                const size_t num_points = f.points.size(); // 获得点数量
                float *polygon_coordinates = f.store();
                TESStesselator *tesselator = tessNewTess(nullptr);
                if (!tesselator) {
                    // error
                    return RenderData();
                }
                tessAddContour(tesselator, 2, polygon_coordinates, sizeof(float) * 2, (int) num_points);
                if (tessTesselate(tesselator, TESS_WINDING_NONZERO, TESS_POLYGONS, 3, 2, nullptr)) {
                    // 获取输出三角形数量、顶点数量
                    const int element_count = tessGetElementCount(tesselator);
                    const int vertex_count = tessGetVertexCount(tesselator);
                    const int index_count = element_count * 3;
                    // 获取输出顶点
                    const float *vertices = tessGetVertices(tesselator);
                    const int *elements = tessGetElements(tesselator);
                    std::cout << "int vertex_offset = " << vertex_offset << ";" << std::endl;
                    data.vertex_offsets.push_back(vertex_offset);
                    vertex_offset += vertex_count;
                    std::cout << "int index_offset = " << index_offset << ";" << std::endl;
                    data.index_offsets.push_back(index_offset);
                    index_offset += index_count;
                    std::cout << "int index_count = " << index_count << ";" << std::endl;
                    std::cout << "int vertex_count = " << vertex_count << ";" << std::endl;
                    data.index_count += index_count;
                    data.vertex_count += vertex_count;
                    std::cout << "DMVertex vertices[] = { " << std::endl;
                    for (int j = 0; j < vertex_count; ++j) {
                        std::cout << "(DMVertex){ { " << vertices[j * 2] << "," << vertices[j * 2 + 1] << ",0,0 } }," << std::endl;
                        data.vertices.push_back({vertices[j * 2], vertices[j * 2 + 1]});
                    }
                    std::cout << " };" << std::endl;
                    std::cout << "UInt16 indices[] = {" << std::endl;
                    for (int j = 0; j < element_count; ++j) {
                        std::cout << elements[j * 3] << "," << elements[j * 3 + 1] << "," << elements[j * 3 + 2] << "," << std::endl;
                        data.indices.push_back(elements[j * 3]);
                        data.indices.push_back(elements[j * 3 + 1]);
                        data.indices.push_back(elements[j * 3 + 2]);
                    }
                    std::cout << "};" << std::endl;
                }
                tessDeleteTess(tesselator);
                free(polygon_coordinates);
            }
            return data;
        }
    };
}

#endif //ABRUSH_FILLTESSELLATOR_H
