#pragma once

#include "vector4.hpp"

struct Color
{
    using ColorChannel = unsigned char;
    using RGBA32 = unsigned int;

    ColorChannel Red = 0;
    ColorChannel Green = 0;
    ColorChannel Blue = 0;
    ColorChannel Alpha = 255;

    Color() = default;
    Color(ColorChannel red, ColorChannel green,
          ColorChannel blue, ColorChannel alpha = 255);

    vector4 RGBAfloat() const;
};
