/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Color.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Color.hpp"

Color::Color(ColorChannel red, ColorChannel green, ColorChannel blue, ColorChannel alpha)
    : Red(red), Green(green), Blue(blue), Alpha(alpha)
{
}

vector4 Color::RGBAfloat() const
{
    return vector4{Red / 255.0f, Green / 255.0f, Blue / 255.0f, Alpha / 255.0f};
}
