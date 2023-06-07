//
// Created by apricity on 2023/6/7.
//

#ifndef UNTITLED_POINT_H
#define UNTITLED_POINT_H

namespace ABrush
{
    class Point
    {
    public:
        float x = 0.0;
        float y = 0.0;

    public:
        Point();

        virtual ~Point();

        Point(float x, float y);

        Point operator+(Point &p) const;

        Point operator-(Point &p);

        Point operator*(Point &p);

        Point operator/(Point &p);

        void setXY(float x, float y);
    };
}

#endif //UNTITLED_POINT_H
