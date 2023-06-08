//
// Created by apricity on 2023/6/7.
//

#include "Point.h"
#include <math.h>

namespace ABrush
{
    Point::Point(double x, double y) : x(x), y(y)
    {}

    Point::~Point()
    = default;

    Point::Point()
    = default;

    Point Point::operator+(Point &p) const
    {
        return {this->x + p.x, this->y + p.y};
    }

    Point Point::operator-(Point &p) const
    {
        return {this->x - p.x, this->y - p.y};
    }

    Point Point::operator*(Point &p) const
    {
        return {this->x * p.x, this->y * p.y};
    }

    Point Point::operator/(double d) const
    {
        return {this->x / d, this->y / d};
    }

    void Point::setXY(double new_x, double new_y)
    {
        x = new_x;
        y = new_y;
    }

    bool Point::operator==(Point &p) const
    {
        return x == p.x &&
               y == p.y;
    }

    Point &Point::operator+=(Point &p)
    {
        this->x += p.x;
        this->y += p.y;
        return *this;
    }

    Point &Point::operator-=(Point &p)
    {
        this->x -= p.y;
        this->y -= p.y;
        return *this;
    }

    Point &Point::operator/=(double d)
    {
        this->x /= d;
        this->y /= d;
        return *this;
    }

    Point Point::operator*(double a) const
    {
        return {this->x * a, this->y * a};
    }

    Point &Point::operator*=(double a)
    {
        this->x *= a;
        this->y *= a;
        return *this;
    }

    Point Point::operator-() const
    {
        return {-this->x, -this->y};
    }

    double Point::length(const Point& p0, const Point& p1)
    {
        double dx = p1.x - p0.x,
               dy  = p1.y - p0.y;
        return sqrt(dx * dx + dy * dy);
    }

    Point operator*(double a, Point &p)
    {
        return {p.x * a, p.y * a};
    }
}