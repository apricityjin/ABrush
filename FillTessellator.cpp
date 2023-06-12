//
// Created by apricity on 2023/6/9.
//

#include "FillTessellator.h"
#include "libtess2/Include/tesselator.h"
#include <iostream>

namespace ABrush
{
    FillTessellator::FillTessellator()
    = default;

    FillTessellator::~FillTessellator()
    = default;

    void FillTessellator::fill(Path &path)
    {
        const size_t num_points = path.points.size(); // 获得点数量
        double * polygon_coordinates = path.store();
        TESStesselator *tesselator = tessNewTess(nullptr);
        if (!tesselator) {
            // error
            return;
        }
        tessAddContour(tesselator, 2, polygon_coordinates, sizeof(double) * 2, (int)num_points);
        if (tessTesselate(tesselator, TESS_WINDING_ODD, TESS_POLYGONS, 3, 2, nullptr)) {
            // 获取输出三角形数量、顶点数量
            const int element_count = tessGetElementCount(tesselator);
            const int vertex_count = tessGetVertexCount(tesselator);
            // 获取输出顶点
            const double *vertices = tessGetVertices(tesselator);
            const int   *elements = tessGetElements(tesselator);
            const int *vertex_indices = tessGetVertexIndices(tesselator);
            std::cout << "int element_count = " << element_count << ";" << std::endl;
            std::cout << "int vertex_count = " << vertex_count << ";" << std::endl;
            for (int i = 0; i < vertex_count; ++i) {
                std::cout << "(DMVertex){ { " << vertices[i * 2] << "," << vertices[i * 2 + 1] <<",0,0 } }," << std::endl;
            }
            for (int i = 0; i < element_count; ++i) {
                std::cout << elements[i * 3] << "," << elements[i * 3 + 1] << "," << elements[i * 3 + 2] << "," << std::endl;
            }
        }

        tessDeleteTess(tesselator);
        free(polygon_coordinates);
    }
}
