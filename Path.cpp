//
// Created by apricity on 2023/6/7.
//

#include "Path.h"

namespace ABrush
{
    Path::Path()
    = default;

    Path::~Path()
    = default;

    Path &Path::moveTo(Point &p)
    {
        Contour c;
        c.commandIndex = commands.size();
        c.pointIndex   = points.size();
        contours.push_back(c);
        commands.push_back(Command::MoveTo);
        points.push_back(p);
        return *this;
    }

    Path &Path::lineTo(Point &p)
    {
        commands.push_back(Command::LineTo);
        points.push_back(p);
        return *this;
    }

    Path &Path::close()
    {
        Contour *c = nullptr;
        if (!contours.empty()) {
            c = &contours.back();
        }
        c->close = true;
        commands.push_back(Command::Close);
        return *this;
    }

    Path &Path::curveTo(Point &p1, Point &p2, Point &endPoint)
    {
        commands.push_back(Command::CurveTo);
        points.push_back(p1);
        points.push_back(p2);
        points.push_back(endPoint);
        return *this;
    }

    Path &Path::moveTo(double x, double y)
    {
        Point p = Point(x, y);
        moveTo(p);
        return *this;
    }

    Path &Path::lineTo(double x, double y)
    {
        Point p = Point(x, y);
        lineTo(p);
        return *this;
    }

    Path &Path::curveTo(double x1, double y1,
                        double x2, double y2,
                        double end_x, double end_y)
    {
        Point p1       = Point(x1, y1);
        Point p2       = Point(x2, y2);
        Point endPoint = Point(end_x, end_y);
        curveTo(p1, p2, endPoint);
        return *this;
    }

    void bezier(std::vector<Point> &bezierPoints,
                std::vector<Point> &velocityPoints,
                Point &start, Point &p1, Point &p2, Point &end)
    {
        bezierPoints.emplace_back(start);
        velocity(velocityPoints, start, p1);
        recursive_bezier(bezierPoints, velocityPoints, 0,
                         start, p1, p2, end);
        bezierPoints.emplace_back(end);
        velocity(velocityPoints, p2, end);
    }

    void recursive_bezier(std::vector<Point> &bezierPoints,
                          std::vector<Point> &velocityPoints,
                          int depth,
                          Point &p0, Point &p1, Point &p2, Point &p3)
    {
        if (depth >= 20) {
            return;
        }
        Point  p01        = (p0 + p1) / 2,
               p12        = (p1 + p2) / 2,
               p23        = (p2 + p3) / 2;
        Point  p012       = (p01 + p12) / 2,
               p123       = (p12 + p23) / 2;
        Point  p0123      = (p012 + p123) / 2;
        double dx         = p3.x - p0.x, dy = p3.y - p0.y;
        double d1         = fabs((p1.x - p3.x) * dy - (p1.y - p3.y) * dx);
        double d2         = fabs((p2.x - p3.x) * dy - (p2.y - p3.y) * dx);
        double m_distance = 1;
        if ((d1 + d2) * (d1 + d2) < m_distance * (dx * dx + dy * dy)) {
            velocity(velocityPoints, p0, p1, p2, p3);
            addPoint(bezierPoints, p0123);
            return;
        }
        recursive_bezier(bezierPoints, velocityPoints, depth + 1,
                         p0, p01, p012, p0123);
        recursive_bezier(bezierPoints, velocityPoints, depth + 1,
                         p0123, p123, p23, p3);
    }

    void velocity(std::vector<Point> &points, Point &p0, Point &p1)
    {
        points.push_back(p1 - p0);
    }

    void ABrush::velocity(std::vector<Point> &points, Point &p0, Point &p1, Point &p2, Point &p3)
    {
        Point p_v = (-p0 - p1 + p2 + p3) * 0.75;
        
        points.push_back(p_v);
    }


}
