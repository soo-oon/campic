/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Color.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

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

	bool isAlphaDone = false;
    vector4 RGBAfloat() const;
};
