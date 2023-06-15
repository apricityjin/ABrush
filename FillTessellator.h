//
// Created by apricity on 2023/6/13.
//

#ifndef ABRUSH_FILLTESSELLATOR_H
#define ABRUSH_FILLTESSELLATOR_H

#include <iostream>
#include "Path.h"
#include "libtess2/Include/tesselator.h"

namespace ABrush
{
    class FillTessellator
    {
    public:
        void fill(Flatten *flattens, size_t size)
        {
            auto f = flattens[0];
            const size_t num_points = f.points.size(); // 获得点数量
            float *polygon_coordinates = f.store();
            TESStesselator *tesselator = tessNewTess(nullptr);
            if (!tesselator) {
                // error
                return;
            }
            tessAddContour(tesselator, 2, polygon_coordinates, sizeof(float) * 2, (int) num_points);
            if (tessTesselate(tesselator, TESS_WINDING_NONZERO, TESS_POLYGONS, 3, 2, nullptr)) {
                // 获取输出三角形数量、顶点数量
                const int   element_count   = tessGetElementCount(tesselator);
                const int   vertex_count    = tessGetVertexCount(tesselator);
                // 获取输出顶点
                const float *vertices       = tessGetVertices(tesselator);
                const int   *elements       = tessGetElements(tesselator);
                const int   *vertex_indices = tessGetVertexIndices(tesselator);
                std::cout << "int element_count = " << element_count << ";" << std::endl;
                std::cout << "int vertex_count = " << vertex_count << ";" << std::endl;
                std::cout << "DMVertex vertices[] = { ";
                for (int i = 0; i < vertex_count; ++i) {
                    std::cout << "(DMVertex){ { " << vertices[i * 2] << "," << vertices[i * 2 + 1] << ",0,0 } },"
                              << std::endl;
                }
                std::cout << " };" << std::endl;
                std::cout << "int elements[] = {";
                for (int i = 0; i < element_count; ++i) {
                    std::cout << elements[i * 3] << "," << elements[i * 3 + 1] << "," << elements[i * 3 + 2] << ","
                              << std::endl;
                }
                std::cout << "};";
            }
            tessDeleteTess(tesselator);
            free(polygon_coordinates);
        }
    };
}

#endif //ABRUSH_FILLTESSELLATOR_H
