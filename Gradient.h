//
// Created by apricity on 2023/6/15.
//

#ifndef ABRUSH_GRADIENT_H
#define ABRUSH_GRADIENT_H

#include <vector>
#include <stdexcept>
#include "Color.h"
#include "Point.h"

namespace ABrush
{

    class Gradient
    {
    public:

        enum class GradientStyle : uint8_t
        {
            Linear,           // 线性渐变（一一对应进行颜色插值，颜色和坐标不对应就取size较小的那个）
            Radial,           // 径向渐变（颜色沿由一个中心点向外的半径方向渐变。）
        };

        Gradient(GradientStyle style, const std::vector<Color> &colors, const std::vector<float> &locations)
                : style(style), colors(colors), locations(locations)
        {}

        explicit Gradient(GradientStyle style)
                : style(style)
        {}

        /// 线性渐变需要颜色与坐标对应
        void add(const Color &color, const float &location)
        {
            colors.push_back(color);
            locations.push_back(location);
        }

        GradientStyle      style;
        /// 储存颜色
        std::vector<Color> colors;
        /// 储存坐标 0.0 ~ 1.0
        std::vector<float> locations;
    };

} // ABrush

#endif //ABRUSH_GRADIENT_H
