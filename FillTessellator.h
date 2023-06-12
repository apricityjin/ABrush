//
// Created by apricity on 2023/6/9.
//

#ifndef ABRUSH_FILLTESSELLATOR_H
#define ABRUSH_FILLTESSELLATOR_H

#include "Path.h"

namespace ABrush
{
    class FillTessellator
    {
    public:
//        int    elementCount;
//        int    vertexCount;
//        double *vertices;
//        int    *elements;
//        int    *vertexIndices;

        FillTessellator();

        virtual ~FillTessellator();

        void fill(Path &path);
    };
}

#endif //ABRUSH_FILLTESSELLATOR_H
