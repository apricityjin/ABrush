//
// Created by apricity on 2023/6/13.
//

#ifndef ABRUSH_POINT_H
#define ABRUSH_POINT_H

#include <cmath>
#include <vector>

namespace ABrush
{
    template<class T>
    typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    almost_equal(T x, T y)
    {
        return std::fabs(x - y) <= std::numeric_limits<T>::epsilon() * std::fabs(x + y) * 2 ||
               std::fabs(x - y) < std::numeric_limits<T>::min();
    }

    class Point
    {
    public:

        Point() : x(0.0), y(0.0)
        {}

        Point(float x, float y) : x(x), y(y)
        {}

        Point(float x, float y, bool normalize) : x(x), y(y)
        {
            if (normalize) {
                this->normalize();
            }
        }

        Point(const Point &aVector2) : x(aVector2.x), y(aVector2.y)
        {}

        Point(const Point &aVector2, bool normalize) : x(aVector2.x), y(aVector2.y)
        {
            if (normalize) {
                this->normalize();
            }
        }

        void set(float aX, float aY)
        {
            x = aX;
            y = aY;
        }

        void set(const Point &aVector2)
        {
            x = aVector2.x;
            y = aVector2.y;
        }

        [[nodiscard]] float length() const
        {
            return sqrt(x * x + y * y);
        }

        void normalize()
        {
            float len = length();
            x /= len;
            y /= len;
        }

        Point &normalized()
        {
            float len = length();
            x /= len;
            y /= len;
            return *this;
        }

        Point operator+(const Point &aVector2) const
        {
            return {x + aVector2.x, y + aVector2.y};
        }

        Point &operator+=(const Point &aVector2)
        {
            this->x += aVector2.x;
            this->y += aVector2.y;
            return *this;
        }

        Point operator-(const Point &aVector2) const
        {
            return {x - aVector2.x, y - aVector2.y};
        }

        Point &operator-=(const Point &aVector2)
        {
            this->x -= aVector2.x;
            this->y -= aVector2.y;
            return *this;
        }

        Point operator*(float s) const
        {
            return {x * s, y * s};
        }

        Point &operator*=(float s)
        {
            this->x *= s;
            this->y *= s;
            return *this;
        }

        Point operator*(const Point &aVector2) const
        {
            return {x * aVector2.x, y * aVector2.y};
        }

        Point &operator*=(const Point &aVector2)
        {
            this->x *= aVector2.x;
            this->y *= aVector2.y;
            return *this;
        }

        Point operator/(float s) const
        {
            return {x / s, y / s};
        }

        Point &operator/=(float s)
        {
            this->x /= s;
            this->y /= s;
            return *this;
        }

        Point operator/(const Point &aVector2) const
        {
            return {x / aVector2.x, y / aVector2.y};
        }

        Point &operator/=(const Point &aVector2)
        {
            this->x /= aVector2.x;
            this->y /= aVector2.y;
            return *this;
        }

        Point operator-() const
        {
            return {-x, -y};
        }

        bool operator==(const Point &aVector2) const
        {
            return almost_equal(x, aVector2.x) &&
                   almost_equal(y, aVector2.y);
        }

        bool operator!=(const Point &aVector2) const
        {
            return !(*this == aVector2);
        }

        float x, y;
        static const size_t size = 2;
    };

    typedef Point Normal;
    typedef Point Tangent;
}


#endif //ABRUSH_POINT_H
