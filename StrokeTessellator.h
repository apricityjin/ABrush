//
// Created by apricity on 2023/6/12.
//

#ifndef ABRUSH_STROKETESSELLATOR_H
#define ABRUSH_STROKETESSELLATOR_H

#include "Path.h"

namespace ABrush
{
    class StrokeTessellator
    {
    public:
        enum class LineJoin: uint8_t
        {
            LineJoinMiter, // 延长相交
            LineJoinRound, // 圆弧过渡
            LineJoinBevel, // 直接连接
        };
        enum class LineCap: uint8_t
        {
            LineCapButt,
            LineCapRound,
            LineCapSquare,
        };
        LineJoin line_join_style = LineJoin::LineJoinBevel;
        LineCap line_cap_style = LineCap::LineCapRound;
        double line_width = 1.0;

        virtual ~StrokeTessellator();

        void stroke(Path &path);
    };
}

#endif //ABRUSH_STROKETESSELLATOR_H
