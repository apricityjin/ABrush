//
// Created by apricity on 2023/6/8.
//

#ifndef ABRUSH_AFFINE_H
#define ABRUSH_AFFINE_H

#include "Path.h"
#include "Point.h"

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

        Affine();

        virtual ~Affine();

        Affine &setIdentity();

        bool isIdentity() const;

        Affine &translate(double x, double y);

        Affine &translateX(double x);

        Affine &translateY(double y);

        Affine &scale(double s);

        Affine &scale(double x, double y);

        Affine &scaleX(double x);

        Affine &scaleY(double y);

        Affine &shear(double x, double y);

        Affine &shearX(double x);

        Affine &shearY(double y);

        Affine &rotate(double a);

        bool operator==(Affine &affine);

        Affine operator*(Affine &affine);

        Affine &operator*=(Affine &affine);

        Affine &multiply(Affine &affine);
    };

    Point operator*(Point &p, Affine &affine);

    Point &operator*=(Point &p, Affine &affine);
}

#endif //ABRUSH_AFFINE_H
