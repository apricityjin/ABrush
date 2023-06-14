//
// Created by apricity on 2023/6/13.
//

#ifndef ABRUSH_PATH_H
#define ABRUSH_PATH_H

#include <vector>
#include "Point.h"

namespace ABrush
{


    void recursive_bezier(std::vector<Point> &bezierPoints,
                          int depth,
                          Point &p0, Point &p1, Point &p2, Point &p3)
    {
        if (depth >= 20) {
            return;
        }
        Point p01        = (p0 + p1) / 2,
              p12        = (p1 + p2) / 2,
              p23        = (p2 + p3) / 2;
        Point p012       = (p01 + p12) / 2,
              p123       = (p12 + p23) / 2;
        Point p0123      = (p012 + p123) / 2;
        float dx         = p3.x - p0.x, dy = p3.y - p0.y;
        float d1         = fabs((p1.x - p3.x) * dy - (p1.y - p3.y) * dx);
        float d2         = fabs((p2.x - p3.x) * dy - (p2.y - p3.y) * dx);
        float m_distance = 1;
        if ((d1 + d2) * (d1 + d2) < m_distance * (dx * dx + dy * dy)) {
            bezierPoints.push_back(p0123);
            return;
        }
        recursive_bezier(bezierPoints,
                         depth + 1,
                         p0, p01, p012, p0123);
        recursive_bezier(bezierPoints,
                         depth + 1,
                         p0123, p123, p23, p3);
    }


    void bezier(std::vector<Point> &bezierPoints,
                Point &start,
                Point &p1,
                Point &p2,
                Point &end)
    {
//        bezierPoints.emplace_back(start);
        recursive_bezier(bezierPoints,
                         0,
                         start, p1, p2, end);
        bezierPoints.emplace_back(end);
    }


    class Path
    {
    public:
        enum class Command : uint8_t
        {
            MoveTo,
            LineTo,
            CurveTo,
            Close,
        };

        struct Contour
        {
            uint32_t pointIndex   = 0;
            uint32_t commandIndex = 0;
            bool     close        = false;
        };
        std::vector<Point>   points;
        std::vector<Command> commands;
        std::vector<Contour> contours;

        Path()
        = default;

        Path &moveTo(Point &p)
        {
            Contour c;
            c.commandIndex = commands.size();
            c.pointIndex   = points.size();
            contours.push_back(c);
            commands.push_back(Command::MoveTo);
            points.push_back(p);
            return *this;
        }

        Path &lineTo(Point &p)
        {
            commands.push_back(Command::LineTo);
            points.push_back(p);
            return *this;
        }

        Path &close()
        {
            Contour *c = nullptr;
            if (!contours.empty()) {
                c = &contours.back();
            }
            c->close = true;
            points.push_back(this->points.at(c->pointIndex));
            commands.push_back(Command::Close);
            return *this;
        }

        Path &curveTo(Point &p1, Point &p2, Point &endPoint)
        {
            commands.push_back(Command::CurveTo);
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(endPoint);
            return *this;
        }

        Path &moveTo(float x, float y)
        {
            Point p = Point(x, y);
            moveTo(p);
            return *this;
        }

        Path &lineTo(float x, float y)
        {
            Point p = Point(x, y);
            lineTo(p);
            return *this;
        }

        Path &curveTo(float x1, float y1,
                      float x2, float y2,
                      float end_x, float end_y)
        {
            Point p1       = Point(x1, y1);
            Point p2       = Point(x2, y2);
            Point endPoint = Point(end_x, end_y);
            curveTo(p1, p2, endPoint);
            return *this;
        }

        Path *flatten()
        {

            Path *p = (Path *)calloc(contours.size(), sizeof(Path));
            int  ptIdx = 0;
            int  PathCount = -1;

            for (Command &cmd: commands) {
                switch (cmd) {

                    case Command::MoveTo:
                        PathCount+= 1;
                        p[PathCount].points.push_back(points.at(ptIdx));
                        ptIdx++;
                        break;
                    case Command::LineTo:
                        p[PathCount].points.push_back(points.at(ptIdx));
                        ptIdx++;
                        break;
                    case Command::CurveTo:
                        bezier(p[PathCount].points,
                               points.at(ptIdx - 1),
                               points.at(ptIdx),
                               points.at(ptIdx + 1),
                               points.at(ptIdx + 2));
                        ptIdx += 3;
                        break;
                    case Command::Close:
                        p[PathCount].points.push_back(p[PathCount].points.at(0));
                        ptIdx++;
                        break;
                }
            }
            return p;
        }

        [[nodiscard]] float *store() const
        {
            size_t points_count = points.size();
            float  *m;
            m = (float *) calloc(points_count * 2, sizeof(float));
            for (int i = 0; i < points_count; ++i) {
                m[i * 2]     = points.at(i).x;
                m[i * 2 + 1] = points.at(i).y;
            }
            return m;
        }


    };

}

#endif //ABRUSH_PATH_H
