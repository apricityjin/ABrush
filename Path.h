//
// Created by apricity on 2023/6/7.
//

#ifndef UNTITLED_PATH_H
#define UNTITLED_PATH_H

#include "Point.h"
#include <vector>

// 我认为遇到 M 指令就是开始一条新的线段
namespace ABrush
{
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

    public:
        Path();

        virtual ~Path();

        Path &moveTo(Point &p);

        Path &moveTo(double x, double y);

        Path &lineTo(Point &p);

        Path &lineTo(double x, double y);

        Path &curveTo(Point &p1, Point &p2, Point &endPoint);

        Path &curveTo(double x1, double y1,
                      double x2, double y2,
                      double end_x, double end_y);

        Path &close();
    };

    void bezier(std::vector<Point> &bezierPoints,
                std::vector<Point> &velocityPoints,
                Point &start,
                Point &p1,
                Point &p2,
                Point &end);

    void recursive_bezier(std::vector<Point> &bezierPoints,
                          std::vector<Point> &velocityPoints,
                          int depth,
                          Point &p0, Point &p1, Point &p2, Point &p3);

    void velocity(std::vector<Point> &points,
                  Point &p0, Point &p1);

    void velocity(std::vector<Point> &points,
                  Point &p0, Point &p1, Point &p2, Point &p3);

    std::vector<Point> normalLines(std::vector<Point> bezierPoints,
                                   std::vector<Point> velocityPoints);
}

#endif //UNTITLED_PATH_H
