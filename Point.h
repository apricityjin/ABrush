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
        double x = 0.0,
               y = 0.0;
    public:
        Point();

        virtual ~Point();

        Point(double x, double y);

        Point operator-() const;

        Point operator+(Point &p) const;

        Point &operator+=(Point &p);

        Point operator-(Point &p) const;

        Point &operator-=(Point &p);

        Point operator*(Point &p) const;

        Point operator*(double a) const;

        Point &operator*=(double a);

        Point operator/(double d) const;

        Point &operator/=(double a);

        void setXY(double x, double y);

        bool operator==(Point &p) const;

        double length(const Point& p0, const Point& p1);
    };

    Point operator*(double a, Point &p);
}

#endif //UNTITLED_POINT_H
