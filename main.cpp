#include <iostream>
#include "ABrush.h"

using namespace std;
using namespace ABrush;

int main()
{
    Point p  = Point(1.0, 1.0);
    Point p1 = Point(2.0, 3.0);
    Point p2 = Point(3.0, 5.0);
    Point p3 = Point(4.0, 7.0);
//    Path path = Path();
//
//    path.moveTo(p);
//    path.lineTo(p1);
//    path.close();
//    path.moveTo(p1);
//    path.lineTo(p2);
//    path.lineTo(p2);
//    path.lineTo(p2);
//    path.moveTo(p);
//    path.lineTo(p1);
//    path.close();
//
//    path.lineTo(p);

    Affine a = Affine().translate(1.0, 2.0).scale(2.0);
    p = p * a;

    vector<Point> bezierPoints;

    bezier(bezierPoints, p,p1,p2,p3);

    return 0;
}
