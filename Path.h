//
// Created by apricity on 2023/6/7.
//

#ifndef UNTITLED_PATH_H
#define UNTITLED_PATH_H

#include "Point.h"
#include <vector>

// 我认为遇到 M 指令就是开始一条新的线段
namespace ABrush {
    class Path {
    public:
        enum class Command : uint8_t {
            MoveTo,
            LineTo,
            CurveTo,
            Close,
        };

        struct Contour {
            uint32_t pointIndex = 0;
            uint32_t commandIndex = 0;
            bool close = false;
        };
        std::vector<Point> points;
        std::vector<Command> commands;
        std::vector<Contour> contours;

    public:
        Path();

        virtual ~Path();

        void moveTo(Point &p);

        void moveTo(float x, float y);

        void lineTo(Point &p);

        void lineTo(float x, float y);

        void curveTo(Point &p1, Point &p2, Point &endPoint);

        void curveTo(float x1, float y1, float x2, float y2, float end_x, float end_y);

        void close();
    };
}

#endif //UNTITLED_PATH_H
