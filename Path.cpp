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

    void Path::moveTo(Point p)
    {
        Contour c;
        c.commandIndex = commands.size();
        c.pointIndex   = points.size();
        contours.push_back(c);
        commands.push_back(Command::MoveTo);
        points.push_back(p);
    }

    void Path::lineTo(Point p)
    {
        commands.push_back(Command::LineTo);
        points.push_back(p);
    }

    void Path::close()
    {
        Contour *c = nullptr;
        if (!contours.empty()) {
            c = &contours.back();
        }
        c->close = true;
        commands.push_back(Command::Close);
    }

    void Path::curveTo(Point p1, Point p2, Point endPoint)
    {
        commands.push_back(Command::CurveTo);
        points.push_back(p1);
        points.push_back(p2);
        points.push_back(endPoint);
    }

    void Path::moveTo(float x, float y)
    {
        moveTo(Point(x, y));
    }

    void Path::lineTo(float x, float y)
    {
        lineTo(Point(x, y));
    }

    void Path::curveTo(float x1, float y1,
                       float x2, float y2,
                       float end_x, float end_y)
    {
        curveTo(Point(x1, y1),
                Point(x2, y2),
                Point(end_x, end_y));
    }

}
