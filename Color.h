//
// Created by apricity on 2023/6/15.
//

#ifndef ABRUSH_COLOR_H
#define ABRUSH_COLOR_H

#include <iostream>

namespace ABrush
{
    /// 直接拷贝到 buffer 里就可以使用
    struct Color
    {
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
                : rgba((a << 24) | (b << 16) | (g << 8) | r)
        {}

        [[nodiscard]] uint8_t r() const
        {
            return rgba & 0xFF;
        }

        [[nodiscard]] uint8_t g() const
        {
            return (rgba >> 8) & 0xFF;
        }

        [[nodiscard]] uint8_t b() const
        {
            return (rgba >> 16) & 0xFF;
        }

        [[nodiscard]] uint8_t a() const
        {
            return (rgba >> 24) & 0xFF;
        }

        void setR(uint8_t r)
        {
            rgba = (rgba & 0xFFFFFF00) | r;
        }

        void setG(uint8_t g)
        {
            rgba = (rgba & 0xFFFF00FF) | (g << 8);
        }

        void setB(uint8_t b)
        {
            rgba = (rgba & 0xFF00FFFF) | (b << 16);
        }

        void setA(uint8_t a)
        {
            rgba = (rgba & 0x00FFFFFF) | (a << 24);
        }

        uint32_t rgba;
    };
} // ABrush

#endif //ABRUSH_COLOR_H
