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
        Gradient(const std::vector<Color> &colors, const std::vector<float> &locations)
                : colors(colors), locations(locations)
        {}

        Gradient()
        = default;

        /// 线性渐变需要颜色与坐标对应
        void add(const Color &color, const float &location)
        {
            colors.push_back(color);
            locations.push_back(location);
        }

        /// 储存颜色
        std::vector<Color> colors;
        /// 储存坐标 0.0 ~ 1.0
        std::vector<float> locations;
    };

} // ABrush

#endif //ABRUSH_GRADIENT_H
