//
// Created by apricity on 2023/6/8.
//

#ifndef ABRUSH_AFFINE_H
#define ABRUSH_AFFINE_H

#include "Path.h"
#include "Point.h"
#include <cmath>

namespace ABrush
{
    /**
     * Affine Transform
     *                     <identity>
     * [sx   shy  0]       [1  0  0]
     * [shx  sy   0]  <=>  [0  1  0]
     * [tx   ty   1]       [0  0  1]
     *
     * 1. translate
     * [1  0  0]   [ 1  0  0]
     * [0  1  0] * [ 0  1  0]
     * [0  0  1]   [tx ty  1]
     *
     * 2. scale
     * [1  0  0]   [sx  0  0]
     * [0  1  0] * [0  sy  0]
     * [0  0  1]   [0   0  1]
     *
     * 3. shear
     * [1  0  0]   [ 1  shy 0]
     * [0  1  0] * [shx  1  0]
     * [0  0  1]   [ 0   0  1]
     *
     * 4. rotate
     * [1  0  0]   [ cos(theta)  sin(theta) 0]
     * [0  1  0] * [-sin(theta)  cos(theta) 0]
     * [0  0  1]   [     0           0      1]
     *
     */
    class Affine
    {
    public:
        double tx  = 0.0,
               ty  = 0.0,
               sx  = 1.0,
               sy  = 1.0,
               shx = 0.0,
               shy = 0.0;

        Affine(double tx, double ty, double sx, double sy, double shx, double shy);

        Affine();

        virtual ~Affine();

        /// 直接输入坐标进行变换
        void transform(double *x, double *y) const;

        /// 不做平移变换
        void transform2x2(double *x, double *y) const;

        Affine &setIdentity();

        [[nodiscard]] bool isIdentity() const;

        Affine &translate(double x, double y);

        Affine &translate(Point &p);

        Affine &translateX(double x);

        Affine &translateY(double y);

        Affine &scale(double s);

        Affine &scale(double x, double y);

        Affine &scale(Point &p);

        Affine &scaleX(double x);

        Affine &scaleY(double y);

        Affine &shear(double x, double y);

        Affine &shearX(double x);

        Affine &shearY(double y);

        Affine &rotate(double a);

        Affine &invert();

        [[nodiscard]] bool isValid() const;

        bool operator==(Affine const &affine) const;

        bool operator!=(Affine &affine) const;

        Affine operator*(Affine &affine);

        Affine &operator*=(Affine &affine);

        Affine operator~() const;

        Affine operator/(Affine &affine) const;
        Affine &operator/=(Affine &affine);

        Affine &multiply(Affine &affine);

        Affine &multiplyInvert(Affine &affine);

        Affine &preMultiply(Affine &affine);

        Affine &preMultiplyInvert(Affine &affine);

        /// 翻转 x
        Affine &flipX();

        /// 翻转 y
        Affine &flipY();

        /// 从数组 m 中加载
        Affine &loadFrom(double *m);

        /// 加载 affine 的数据
        void storeTo(double *m) const;
    };

    Point operator*(Point &p, Affine &affine);

    Point &operator*=(Point &p, Affine &affine);
}

#endif //ABRUSH_AFFINE_H
