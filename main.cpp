#include <iostream>
#include "ABrush.h"

using namespace ABrush;

int main()
{
    Point p0   = Point(100.0, 50.0);
    Point p1   = Point(60.0, 300.0);
    Point p2   = Point(200.0, 150.0);
    Point p3   = Point(300.0, 400.0);
    Point p4   = Point(200.0, 400.0);
    Point p5   = Point(150.0, 100.0);
    Path  path = Path();
    path
            .moveTo(p0).lineTo(p1)
            .moveTo(p5).curveTo(p2, p3, p4).close();

    Flatten * flattens = path.flatten();
//    FillTessellator tessellator = FillTessellator();
//    tessellator.fill(flattenPath, path.contours.size());
    StrokeTessellator tessellator = StrokeTessellator();
    tessellator.line_join_style = StrokeTessellator::LineJoin::LineJoinMiter;
    tessellator.line_width = 5.0;
    tessellator.line_cap_style = StrokeTessellator::LineCap::LineCapRound;
    tessellator.stroke(flattens, path.contours.size());
    return 0;
}
