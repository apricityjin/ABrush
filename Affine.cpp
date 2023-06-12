//
// Created by apricity on 2023/6/8.
//

#include "Affine.h"

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y)
{
    return std::fabs(x - y) <= std::numeric_limits<T>::epsilon() * std::fabs(x + y) * 2
           || std::fabs(x - y) < std::numeric_limits<T>::min();
}

namespace ABrush
{
    Point operator*(Point &p, Affine &affine)
    {
        Point result = Point();
        result.x = p.x * affine.sx + p.y * affine.shx + affine.tx;
        result.y = p.x * affine.shy + p.y * affine.sy + affine.ty;
        return result;
    }

    Point &operator*=(Point &p, Affine &affine)
    {
        double x = p.x, y = p.y;
        p.x = x * affine.sx + y * affine.shx + affine.tx;
        p.y = x * affine.shy + y * affine.sy + affine.ty;
        return p;
    }

    Affine &Affine::translate(double x, double y)
    {
        tx += x;
        ty += y;
        return *this;
    }

    Affine &Affine::scale(double s)
    {
        sx *= s;
        sy *= s;
        tx *= s;
        ty *= s;
        shx *= s;
        shy *= s;
        return *this;
    }

    Affine &Affine::rotate(double a)
    {
        double ca = cos(a);
        double sa = sin(a);
        double t0 = sx * ca - shy * sa;
        double t2 = shx * ca - sy * sa;
        double t4 = tx * ca - ty * sa;
        shy = sx * sa + shy * ca;
        sy  = shx * sa + sy * ca;
        ty  = tx * sa + ty * ca;
        sx  = t0;
        shx = t2;
        tx  = t4;
        return *this;
    }

    Affine &Affine::translateX(double x)
    {
        tx += x;
        return *this;
    }

    Affine &Affine::translateY(double y)
    {
        ty += y;
        return *this;
    }

    Affine &Affine::scaleX(double x)
    {
        sx *= x;
        shx *= x;
        tx *= x;
        return *this;
    }

    Affine &Affine::scaleY(double y)
    {
        shy *= y;
        sy *= y;
        ty *= y;
        return *this;
    }

    Affine &Affine::shear(double x, double y)
    {
        sx += shy * x;
        shx += sy * x;
        tx += ty * x;
        sy += shx * y;
        shy += sx * y;
        ty += tx * y;
        return *this;
    }

    Affine &Affine::shearX(double x)
    {
        sx += shy * x;
        shx += sy * x;
        tx += ty * x;
        return *this;
    }

    Affine &Affine::shearY(double y)
    {
        sy += shx * y;
        shy += sx * y;
        ty += tx * y;
        return *this;
    }

    Affine &Affine::scale(double x, double y)
    {
        sx *= x;
        shx *= x;
        tx *= x;
        shy *= y;
        sy *= y;
        ty *= y;
        return *this;
    }

    Affine::~Affine()
    = default;

    Affine::Affine() : tx(0.0), ty(0.0),
                       sx(1.0), sy(1.0),
                       shx(0.0), shy(0.0)
    {}

    bool Affine::operator==(Affine const &affine) const {
        return almost_equal(sx, affine.sx) &&
               almost_equal(shx, affine.shx) &&
               almost_equal(shy, affine.shy) &&
               almost_equal(sy, affine.sy) &&
               almost_equal(tx, affine.tx) &&
               almost_equal(ty, affine.ty);
    }

    Affine &Affine::multiply(ABrush::Affine &affine)
    {
        double t0 = sx * affine.sx + shy * affine.shx;
        double t2 = shx * affine.sx + sy * affine.shx;
        double t4 = tx * affine.sx + ty * affine.shx + affine.tx;
        shy = sx * affine.shy + shy * affine.sy;
        sy  = shx * affine.shy + sy * affine.sy;
        ty  = tx * affine.shy + ty * affine.sy + affine.ty;
        sx  = t0;
        shx = t2;
        tx  = t4;
        return *this;
    }

    Affine Affine::operator*(Affine &affine)
    {
        Affine result = *this;
        result *= affine;
        return result;
    }

    Affine &Affine::operator*=(Affine &affine)
    {
        multiply(affine);
        return *this;
    }

    Affine &Affine::setIdentity()
    {
        sx = sy = 1.0;
        tx = ty = shx = shy = 0.0;
        return *this;
    }

    bool Affine::isIdentity() const
    {
        return sx == 1.0 &&
               sy == 1.0 &&
               tx == 0.0 &&
               ty == 0.0 &&
               shx == 0.0 &&
               shy == 0.0;
    }

    Affine &Affine::scale(Point &p)
    {
        return scale(p.x, p.y);
    }

    Affine &Affine::translate(Point &p)
    {
        return translate(p.x, p.y);
    }

    Affine &Affine::invert()
    {
        double d  = static_cast<double>(1) / (sx * sy - shy * shx);
        double t0 = sy * d;
        sy  = sx * d;
        shy = -shy * d;
        shx = -shx * d;

        double t4 = -tx * t0 - ty * shx;
        ty = -tx * shy - ty * sy;

        sx = t0;
        tx = t4;
        return *this;
    }

    bool Affine::isValid() const
    {
        return sx != 0.0 &&
               sy != 0.0;
    }

    Affine Affine::operator~() const
    {
        Affine result = *this;
        result.invert();
        return result;
    }

    bool Affine::operator!=(Affine &affine) const
    {
        return !(*this == affine);
    }

    Affine &Affine::flipX()
    {
        sx  = -sx;
        shy = -shy;
        tx  = -tx;
        return *this;
    }

    Affine &Affine::flipY()
    {
        shx = -shx;
        sy  = -sy;
        ty  = -ty;
        return *this;
    }

    Affine::Affine(double tx, double ty, double sx, double sy, double shx, double shy) :
            tx(tx), ty(ty), sx(sx), sy(sy), shx(shx), shy(shy)
    {}

    void Affine::transform(double *x, double *y) const
    {
        double temp = *x;
        *x = temp * sx + *y * shx + tx;
        *y = temp * shy + *y * sy + ty;
    }

    void Affine::transform2x2(double *x, double *y) const
    {
        double temp = *x;
        *x = temp * sx + *y * shx;
        *y = temp * shy + *y * sy;
    }

    Affine &Affine::multiplyInvert(Affine &affine)
    {
        Affine t = affine;
        t.invert();
        return multiply(t);
    }

    Affine &Affine::preMultiply(Affine &affine)
    {
        Affine t = affine;
        return *this = t.multiply(*this);
    }

    Affine &Affine::preMultiplyInvert(Affine &affine)
    {
        Affine t = affine;
        t.invert();
        return *this = t.multiply(*this);
    }

    Affine Affine::operator/(Affine &affine) const
    {
        Affine result = *this;
        result /= affine;
        return result;
    }

    Affine &Affine::operator/=(Affine &affine)
    {
        preMultiply(affine);
        return *this;
    }

    Affine &Affine::loadFrom(double *m)
    {
        sx  = *m++;
        shy = *m++;
        shx = *m++;
        sy  = *m++;
        tx  = *m++;
        ty  = *m++;
        return *this;
    }

    void Affine::storeTo(double *m) const
    {
        *m++ = sx;
        *m++ = shy;
        *m++ = shx;
        *m++ = sy;
        *m++ = tx;
        *m++ = ty;
    }
}
