//
// Created by apricity on 2023/6/13.
//

#ifndef ABRUSH_STROKETESSELLATOR_H
#define ABRUSH_STROKETESSELLATOR_H

#include "Path.h"
#include "Affine.h"
#include <cmath>

namespace ABrush
{
    class StrokeTessellator
    {
    public:
        /// 交点风格
        enum class LineJoin : uint8_t
        {
            LineJoinMiter, // 延长相交
            LineJoinRound, // 圆弧过渡
            LineJoinBevel, // 直接连接
        };
        /// 端点风格
        enum class LineCap : uint8_t
        {
            LineCapRound,
            LineCapSquare,
        };
        LineJoin line_join_style = LineJoin::LineJoinBevel;
        LineCap  line_cap_style  = LineCap::LineCapSquare;
        float    line_width      = 1.0;

        void stroke(Flatten *flattens, size_t size)
        {
            using namespace std;
            for (size_t pathIdx = 0; pathIdx < size; ++pathIdx) {
                Flatten       &f      = flattens[pathIdx];
                vector<Point> &points = f.points;
                int           ptCount = f.points.size();
                if (ptCount <= 1) continue; // 只有一个点无法绘画，这里直接进行跳过处理
                vector<Point>    vertices;
                int              vertex_count  = 0;
                vector<uint32_t> elements;
                int              element_count = 0;

                if (line_cap_style == LineCap::LineCapRound && !f.isClosed) {
                    Point &start = points[0],
                          &end   = points[1];
                    vertices.push_back(start);
                    vertex_count += 1;
                    Point tangent = (end - start).normalized();
                    Point n_left  = Point(-tangent.y, tangent.x) * line_width;
                    Point left    = start + n_left;
                    vertices.push_back(left);
                    vertex_count += 1;
                    float angle     = M_PI;
                    float tolerance = 0.1;
                    float &radius   = line_width;
                    tolerance = std::min(tolerance, radius);
                    float step      = std::sqrt(2.0 * tolerance * radius - tolerance * tolerance) * 2.0;
                    float arcLength = angle * radius;
                    int   segment   = std::ceil(arcLength / step);
                    if (segment < 2) segment = 2;
                    Affine   a    = Affine().rotate(angle / segment);
                    for (int i    = 0; i < segment; ++i) {
                        n_left *= a;
                        left = start + n_left;
                        vertices.push_back(left);
                        vertex_count += 1;
                    }
                    element_count = vertex_count - 2;
                    uint32_t j;
                    for (j = 0; j < element_count; ++j) {
                        elements.push_back(0);
                        elements.push_back(j + 1);
                        elements.push_back(j + 2);
                    }
                }

                // LineJoinBevel
                if (line_join_style == LineJoin::LineJoinBevel) {
                    // 第一个点
                    int   vertexIdx = 0;
                    Point &start    = points.at(vertexIdx),
                          &end      = points.at(vertexIdx + 1);
                    Point tangent   = (end - start).normalized();
                    Point n_left    = Point(-tangent.y, tangent.x) * line_width;
                    Point n_right   = Point(tangent.y, -tangent.x) * line_width;
                    Point left      = start + n_left;
                    Point right     = start + n_right;
                    vertices.push_back(left);
                    vertices.push_back(right);
                    vertex_count += 2;
                    // 中间的点
                    for (vertexIdx  = 1; vertexIdx < ptCount - 1; ++vertexIdx) {
                        // 作为终点
                        left    = end + n_left;
                        right   = end + n_right;
                        vertices.push_back(left);
                        vertices.push_back(right);
                        vertex_count += 2;
                        // 作为起点
                        start   = points.at(vertexIdx);
                        end     = points.at(vertexIdx + 1);
                        tangent = (end - start).normalized();
                        n_left  = Point(-tangent.y, tangent.x) * line_width;
                        n_right = Point(tangent.y, -tangent.x) * line_width;
                        left    = start + n_left;
                        right   = start + n_right;
                        vertices.push_back(left);
                        vertices.push_back(right);
                        vertex_count += 2;
                    }
                    // 最后一个点，如果是闭合线段，需要特殊处理
                    left            = end + n_left;
                    right           = end + n_right;
                    vertices.push_back(left);
                    vertices.push_back(right);
                    vertex_count += 2;
                    //闭合曲线的处理
                    if (f.isClosed) {
                        vertices.push_back(vertices[0]);
                        vertices.push_back(vertices[1]);
                        vertex_count += 2;
                    }
                    uint32_t j = element_count;
                    element_count = vertex_count - 2;
                    for (; j < element_count; ++j) {
                        elements.push_back(j);
                        elements.push_back(j + 1);
                        elements.push_back(j + 2);
                    }
                }
                    // LineJoinMiter
                else if (line_join_style == LineJoin::LineJoinMiter) {

                    // 第一个点
                    int   vertexIdx     = 0;
                    Point start         = points.at(vertexIdx),
                          end           = points.at(vertexIdx + 1);
                    Point tangent       = (end - start).normalized();
                    Point n_left        = Point(-tangent.y, tangent.x) * line_width;
                    Point n_right       = Point(tangent.y, -tangent.x) * line_width;
                    Point n_left_start  = n_left;
                    Point n_right_start = n_right;
                    Point left          = start + n_left;
                    Point right         = start + n_right;
                    vertices.push_back(left);
                    vertices.push_back(right);
                    vertex_count += 2;
                    // 中间的点
                    for (vertexIdx      = 1; vertexIdx < ptCount - 1; ++vertexIdx) {
                        Point p0 = n_left;
                        Point p1 = n_right;
                        start   = points.at(vertexIdx);
                        end     = points.at(vertexIdx + 1);
                        tangent = (end - start).normalized();
                        Point &p2       = n_left  = Point(-tangent.y, tangent.x) * line_width;
                        Point &p3       = n_right = Point(tangent.y, -tangent.x) * line_width;
                        float H         = sqrt((p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y));
                        float cos_angle = (line_width * line_width * 2 - H * H) / (2 * line_width * line_width);
                        if (almost_equal(cos_angle, static_cast<float>(-1))) {
                            vertices.push_back(start + n_left);
                            vertices.push_back(start + n_right);
                            vertex_count += 2;
                        } else {
                            float cos_angle_2 = sqrt((1 + cos_angle) / 2);
                            float L           = line_width / cos_angle_2;
                            Point l           = (p0 + p2).normalized() * L + start;
                            Point r           = (p1 + p3).normalized() * L + start;
                            vertices.push_back(l);
                            vertices.push_back(r);
                            vertex_count += 2;
                        }
                    }

                    // 最后一个点
                    left  = end + n_left;
                    right = end + n_right;
                    vertices.push_back(left);
                    vertices.push_back(right);
                    vertex_count += 2;

                    // 闭合曲线的处理
                    if (f.isClosed) {
                        float H           = sqrt((n_left.x - n_left_start.x) * (n_left.x - n_left_start.x) +
                                                 (n_left.y - n_left_start.y) * (n_left.y - n_left_start.y));
                        float cos_angle   = (line_width * line_width * 2 - H * H) / (2 * line_width * line_width);
                        if (almost_equal(cos_angle, static_cast<float>(-1))) {
                            vertices.push_back(start + n_left);
                            vertices.push_back(start + n_right);
                            vertex_count += 2;
                        } else {
                            float cos_angle_2 = sqrt((1 + cos_angle) / 2);
                            float L           = line_width / cos_angle_2;
                            Point l           = (n_left + n_left_start).normalized() * L + end;
                            Point r           = (n_right + n_right_start).normalized() * L + end;
                            vertices.push_back(l);
                            vertices.push_back(r);
                            vertex_count += 2;
                        }
                        vertices.push_back(vertices[0]);
                        vertices.push_back(vertices[1]);
                        vertex_count += 2;
                    }
                    uint32_t j = element_count;
                    element_count = vertex_count - 2;
                    for (j; j < element_count; ++j) {
                        elements.push_back(j);
                        elements.push_back(j + 1);
                        elements.push_back(j + 2);
                    }
                }
                    // LineJoinRound
                else if (line_join_style == LineJoin::LineJoinRound) {
                    // 处理起点
                    int      vertexIdx     = 0;
                    Point    start         = points.at(vertexIdx),
                             end           = points.at(vertexIdx + 1);
                    Point    tangent       = (end - start).normalized();
                    Point    n_left        = Point(-tangent.y, tangent.x) * line_width;
                    Point    n_right       = Point(tangent.y, -tangent.x) * line_width;
                    Point    n_left_start  = n_left;
                    Point    n_right_start = n_right;
                    Point    left          = start + n_left;
                    Point    right         = start + n_right;
                    vertices.push_back(left);
                    vertices.push_back(right);
                    vertex_count += 2;
                    for (vertexIdx         = 1; vertexIdx < ptCount - 1; ++vertexIdx) {
                        Point p0 = n_left;
                        Point p1 = n_right;
                        left    = end + n_left;
                        right   = end + n_right;
                        vertices.push_back(left);
                        vertices.push_back(right);
                        vertex_count += 2;
                        // 计算圆弧
                        /*
                        auto circleFlatteningStep = [](float radius, float tolerance) {
                            tolerance = std::min(tolerance, radius);
                            return 2.0 * std::sqrt(2.0 * tolerance * radius - tolerance * tolerance);
                        };
                        float arcLength = M_PI * radius * 2.0;
                        float step = circleFlatteningStep(radius, 0.1);
                        int segment = std::ceil(arcLength / step);
                         */
                        start   = points.at(vertexIdx);
                        end     = points.at(vertexIdx + 1);
                        tangent = (end - start).normalized();
                        Point &p2       = n_left  = Point(-tangent.y, tangent.x) * line_width;
                        Point &p3       = n_right = Point(tangent.y, -tangent.x) * line_width;
                        float H         = sqrt((p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y));
                        float cos_angle = (line_width * line_width * 2 - H * H) / (2 * line_width * line_width);
                        float angle     = acos(cos_angle);

                        float tolerance = 0.1;
                        float &radius   = line_width;
                        tolerance = std::min(tolerance, radius);
                        float step      = std::sqrt(2.0 * tolerance * radius - tolerance * tolerance) * 2.0;
                        float arcLength = angle * radius;
                        int   segment   = std::ceil(arcLength / step);
                        if (segment < 2) segment = 2;

                        Affine   a = Affine().rotate(angle / segment);
                        for (int i = 0; i < segment + 1; ++i) {
                            p0 *= a;
                            p1 *= a;
                            left  = start + p0;
                            right = start + p1;
                            vertices.push_back(left);
                            vertices.push_back(right);
                            vertex_count += 2;
                        }
                        left       = start + n_left;
                        right      = start + n_right;
                        vertices.push_back(left);
                        vertices.push_back(right);
                        vertex_count += 2;
                    }
                    // 处理终点
                    left                   = end + n_left;
                    right                  = end + n_right;
                    vertices.push_back(left);
                    vertices.push_back(right);
                    vertex_count += 2;
                    if (f.isClosed) {
                        // 闭合处理
                        float H         = sqrt((n_left.x - n_left_start.x) * (n_left.x - n_left_start.x) +
                                               (n_left.y - n_left_start.y) * (n_left.y - n_left_start.y));
                        float cos_angle = (line_width * line_width * 2 - H * H) / (2 * line_width * line_width);
                        float angle     = acos(cos_angle);
                        float tolerance = 0.1;
                        float &radius   = line_width;
                        tolerance       = std::min(tolerance, radius);
                        float step      = std::sqrt(2.0 * tolerance * radius - tolerance * tolerance) * 2.0;
                        float arcLength = angle * radius;
                        int   segment   = std::ceil(arcLength / step);
                        if (segment < 2) segment = 2;
                        Affine   a = Affine().rotate(angle / segment);
                        for (int i = 0; i < segment; ++i) {
                            n_left *= a;
                            n_right *= a;
                            left  = end + n_left;
                            right = end + n_right;
                            vertices.push_back(left);
                            vertices.push_back(right);
                            vertex_count += 2;
                        }
                    }
                    uint32_t j             = element_count;
                    element_count = vertex_count - 2;
                    for (; j < element_count; ++j) {
                        elements.push_back(j);
                        elements.push_back(j + 1);
                        elements.push_back(j + 2);
                    }
                }
                // 结束点的处理
                if (line_cap_style == LineCap::LineCapRound && !f.isClosed) {
                    Point    &start  = points[ptCount - 2],
                             &end    = points[ptCount - 1];
                    uint32_t end_idx = vertex_count;
                    vertices.push_back(end);
                    vertex_count += 1;
                    Point tangent = (end - start).normalized();
                    Point n_right = Point(tangent.y, -tangent.x) * line_width;
                    Point right   = end + n_right;
                    vertices.push_back(right);
                    vertex_count += 1;
                    float angle     = M_PI;
                    float tolerance = 0.1;
                    float &radius   = line_width;
                    tolerance = std::min(tolerance, radius);
                    float step      = std::sqrt(2.0 * tolerance * radius - tolerance * tolerance) * 2.0;
                    float arcLength = angle * radius;
                    int   segment   = std::ceil(arcLength / step);
                    if (segment < 2) segment = 2;
                    Affine   a    = Affine().rotate(angle / segment);
                    for (int i    = 0; i < segment; ++i) {
                        n_right *= a;
                        right = end + n_right;
                        vertices.push_back(right);
                        vertex_count += 1;
                    }
                    element_count = vertex_count - 2;
                    uint32_t j = end_idx;
                    for (; j < element_count; ++j) {
                        elements.push_back(end_idx);
                        elements.push_back(j + 1);
                        elements.push_back(j + 2);
                    }

                    element_count -= 2;
                }
                std::cout << "int vertex_count = " << vertex_count << ";" << std::endl;
                std::cout << "DMVertex vertices[] = { " << std::endl;
                for (int j = 0; j < vertex_count; ++j) {
                    std::cout << "(DMVertex){ { " << vertices[j].x << "," << vertices[j].y << ",0,0 } },"
                              << std::endl;
                }
                std::cout << " };" << std::endl;
                std::cout << "int element_count = " << element_count << ";" << std::endl;
                std::cout << "int elements[] = {";
                for (int k = 0; k < element_count; ++k) {
                    std::cout << elements[k * 3] << "," << elements[k * 3 + 1] << "," << elements[k * 3 + 2] << ","
                              << std::endl;
                }
                std::cout << "};" << std::endl;
            }
        }
    };
}

#endif //ABRUSH_STROKETESSELLATOR_H
