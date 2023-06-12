//
// Created by apricity on 2023/6/12.
//

#include "StrokeTessellator.h"
#include "libtess2/Include//tesselator.h"
#include <iostream>

namespace ABrush
{
    void StrokeTessellator::stroke(Path &path)
    {
        line_width = 5;
        const size_t points_count         = path.points.size(); // 获得点数量
        const size_t normal_pts_count     = (points_count - 1) * 2;
        double       *polygon_coordinates = path.store();
        double       *left_normal_points  = (double *) calloc(normal_pts_count, sizeof(double) * 2);
        double       *right_normal_points = (double *) calloc(normal_pts_count, sizeof(double) * 2);
        double *normal_points = (double *) calloc(normal_pts_count * 2, sizeof(double ) * 2);
        for (int       i           = 0; i < points_count - 1; ++i) {
            double start_x    = polygon_coordinates[i * 2],
                   start_y    = polygon_coordinates[i * 2 + 1],
                   end_x      = polygon_coordinates[i * 2 + 2],
                   end_y      = polygon_coordinates[i * 2 + 3];
            double velocity_y = end_y - start_y,
                   velocity_x = end_x - start_x;
            double length     = sqrt(velocity_y * velocity_y + velocity_x * velocity_x);
            velocity_y = velocity_y * line_width / length;
            velocity_x = velocity_x * line_width / length;
            left_normal_points[i * 4]      = -velocity_y + start_x;
            left_normal_points[i * 4 + 1]  = velocity_x + start_y;
            left_normal_points[i * 4 + 2]  = -velocity_y + end_x;
            left_normal_points[i * 4 + 3]  = velocity_x + end_y;
            right_normal_points[i * 4]     = velocity_y + start_x;
            right_normal_points[i * 4 + 1] = -velocity_x + start_y;
            right_normal_points[i * 4 + 2] = velocity_y + end_x;
            right_normal_points[i * 4 + 3] = -velocity_x + end_y;
        }
        TESStesselator *tesselator = tessNewTess(nullptr);
        if (!tesselator) {
            // error
            return;
        }
        tessAddContour(tesselator, 2, left_normal_points, sizeof(double) * 2, (int) normal_pts_count);
        tessAddContour(tesselator, 2, right_normal_points, sizeof(double) * 2, (int) normal_pts_count);
        if (tessTesselate(tesselator, TESS_WINDING_ODD, TESS_POLYGONS, 3, 2, nullptr)) {
            // 获取输出三角形数量、顶点数量
            const int    element_count   = tessGetElementCount(tesselator);
            const int    vertex_count    = tessGetVertexCount(tesselator);
            // 获取输出顶点
            const double *vertices       = tessGetVertices(tesselator);
            const int    *elements       = tessGetElements(tesselator);
            std::cout << "int element_count = " << element_count << ";" << std::endl;
            std::cout << "int vertex_count = " << vertex_count << ";" << std::endl;
            std::cout << "DMVertex vertices[] = { ";
            for (int i = 0; i < vertex_count; ++i) {
                std::cout << "(DMVertex){ { " << vertices[i * 2] << "," << vertices[i * 2 + 1] << ",0,0 } },"
                          << std::endl;
            }
            std::cout << " };" << std::endl;
            std::cout << "int indices[] = {";
            for (int i = 0; i < element_count; ++i) {
                std::cout << elements[i * 3] << "," << elements[i * 3 + 1] << "," << elements[i * 3 + 2] << ","
                          << std::endl;
            }
            std::cout << "};";
        }
    }

    StrokeTessellator::~StrokeTessellator()
    = default;
}
