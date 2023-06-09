#include <iostream>
#include "ABrush.h"

using namespace std;
using namespace ABrush;

int main()
{
//    Point p    = Point(1.0, 1.0);
//    Point p1   = Point(2.0, 3.0);
//    Point p2   = Point(3.0, 5.0);
//    Point p3   = Point(4.0, 7.0);
//    Path  path = Path();
//
//    path.moveTo(p).lineTo(p1).close().moveTo(p3).curveTo(p, p1, p2).close();
//
//    Affine a = Affine().translate(1.0, 2.0).scale(2.0);
//    p = p * a;

    vector<Point> bezierPoints;
    vector<Point> velocityPoints;

    Point p0 = Point(100, 100),
          p1 = Point(200, 100),
          p2 = Point(200, 300),
          p3 = Point(100, 300);

    bezier(bezierPoints, velocityPoints, p0, p1, p2, p3);

    return 0;
}
