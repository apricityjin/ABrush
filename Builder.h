//
// Created by apricity on 2023/6/15.
//

#ifndef ABRUSH_BUILDER_H
#define ABRUSH_BUILDER_H

#include "Color.h"
#include "Image.h"
#include "FillTessellator.h"
#include "StrokeTessellator.h"

namespace ABrush
{
    class Builder
    {
    public:
        Builder()
        = default;

        void setFillColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        {
            fillColor.setRGBA(r, g, b, a);
        }

        void setFillColor(const Color &color)
        {
            fillColor = color;
        }

        void setStrokeColor(const Color &color)
        {
            strokeColor = color;
        }

        void setStrokeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        {
            strokeColor.setRGBA(r, g, b, a);
        }

        void setLineWidth(float width)
        {
            lineWidth = width;
        }

        void addPath(Path &p)
        {
            paths.push_back(p);
        }



        Color fillColor;
        Color strokeColor;
        float lineWidth = 1.0;
        Image *image    = nullptr;
        std::vector<Path> paths;
    };
}

#endif //ABRUSH_BUILDER_H
