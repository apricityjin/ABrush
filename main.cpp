#include <iostream>
#include <simd/simd.h>
#include "ABrush.h"

using namespace ABrush;
using namespace std;

int main()
{
    Point p0 = Point(100.0, 50.0);
    Point p1 = Point(60.0, 300.0);
    Point p2 = Point(200.0, 150.0);
    Point p3 = Point(300.0, 400.0);
    Point p4 = Point(200.0, 400.0);
    Point p5 = Point(150.0, 100.0);
    Path path = Path();
    path
            .moveTo(p0).lineTo(p1).lineTo(p2).lineTo(p4)
            .moveTo(p5).curveTo(p2, p3, p4).close();

    Flatten *flattens = path.flatten();
    FillTessellator tessellator = FillTessellator();
    RenderData data = tessellator.fill(flattens);
//    StrokeTessellator tessellator = StrokeTessellator();
//    tessellator.line_join_style = StrokeTessellator::LineJoin::LineJoinRound;
//    tessellator.line_width = 10.0;
//    tessellator.line_cap_style = StrokeTessellator::LineCap::LineCapRound;
//    RenderData data = tessellator.stroke(flattens);
/*
    vector<Color> colors = {
//            {11, 0,   0,   255},
//            {0,   55, 0,   255},
//            {0,   0,   66, 255},
//            {22, 0,   0,   255},
//            {0,   33, 0,   255},
//            {0,   0,   44, 255},
            {11, 0, 0, 0},
            {55, 0, 0, 0},
            {66, 0, 0, 0},
//            {22, 0, 0, 0},
//            {33, 0, 0, 0},
//            {44, 0, 0, 0},
    };
    vector<float> locations = {
            0.0,
            0.5,
            1.0,
//            0.01,
//            0.02,
//            0.05,
    };
    Gradient g = Gradient(colors, locations);
    Builder b = Builder();
//    b.drawLinearGradient(g, p0, p4);
//    b.drawRadialGradient(g, p5, 50);
 */
    return 0;
}
