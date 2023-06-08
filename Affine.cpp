//
// Created by apricity on 2023/6/8.
//

#include "Affine.h"

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

    bool Affine::operator==(Affine &affine)
    {
        return tx == affine.tx &&
               ty == affine.ty &&
               sx == affine.sx &&
               sy == affine.sy &&
               shx == affine.shx &&
               shy == affine.shy;
    }

    Affine &Affine::multiply(ABrush::Affine &affine)
    {
        double t0 = sx  * affine.sx + shy * affine.shx;
        double t2 = shx * affine.sx + sy  * affine.shx;
        double t4 = tx  * affine.sx + ty  * affine.shx + affine.tx;
        shy = sx  * affine.shy + shy * affine.sy;
        sy  = shx * affine.shy + sy  * affine.sy;
        ty  = tx  * affine.shy + ty  * affine.sy + affine.ty;
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
}
