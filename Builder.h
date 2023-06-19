//
// Created by apricity on 2023/6/15.
//

#ifndef ABRUSH_BUILDER_H
#define ABRUSH_BUILDER_H

#include "Color.h"
#include "Image.h"
#include "FillTessellator.h"
#include "StrokeTessellator.h"
#include "Gradient.h"

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

        /// 线性渐变（一一对应进行颜色插值，颜色和坐标数量不对应就取size较小的那个）
        uint32_t *drawLinearGradient(Gradient &g, Point &start, Point &end)
        {

            // count = 0 -> 不用渲染，count = 1 -> 只用渲染一种颜色， count >= 2 -> 颜色插值运算
            uint32_t count   = std::min(g.colors.size(), g.locations.size());
            uint32_t *buffer = nullptr;
            if (count == 0) {
                return nullptr;
            } else if (count == 1) {
                Color &c = g.colors[0];
                buffer = (uint32_t *) calloc(1, sizeof(uint32_t));
                *buffer = c.rgba;
                return buffer;
            } // count >= 2
            // 默认切割256份
            uint32_t size    = 256;
            buffer = (uint32_t *) calloc(size, sizeof(uint32_t));
            uint32_t *pointer = buffer;
            int   l             = 0,
                  r             = 1;
            Color leftColor     = g.colors[l];
            Color rightColor    = g.colors[r];
            Color curColor      = leftColor;
            float leftLocation  = g.locations[l];
            float rightLocation = g.locations[r];
            float curLocation;

            for (int i = 0; i < size; ++i) {
                curLocation = (float) i / (float) (size - 1);
                if (curLocation < leftLocation) {
                    *pointer++ = curColor.rgba;
                    continue;
                }
                float len      = rightLocation - leftLocation,
                      rPercent = (curLocation - leftLocation) / len,
                      lPercent = 1 - rPercent;
                uint32_t res = rgbaInterpolation(leftColor, lPercent, rightColor, rPercent);
                *pointer++ = res;
            }

            return buffer;
        }

        /// 径向渐变（颜色沿由一个中心点向外的半径方向渐变。）
        uint32_t *drawRadialGradient(Gradient &g, Point &center, float radius)
        {
            // 默认切割256份
            uint32_t size    = 256;
            uint32_t *buffer = (uint32_t *) calloc(size + 1, sizeof(uint32_t));

            for (int i = 0; i < 256; ++i) {

            }

            return buffer;
        }

        Color             fillColor;
        Color             strokeColor;
        float             lineWidth = 1.0;
        Image             *image    = nullptr;
        std::vector<Path> paths;
    };
}

#endif //ABRUSH_BUILDER_H
