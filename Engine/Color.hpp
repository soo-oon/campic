#pragma once

#include <glm/vec4.hpp>

struct Color
{
	using ColorChannel = unsigned char;
	using RGBA32 = unsigned int;

	ColorChannel Red = 0;
	ColorChannel Green = 0;
	ColorChannel Blue = 0;
	ColorChannel Alpha = 0;

	Color() = default;
	Color(ColorChannel red, ColorChannel green,
		ColorChannel blue, ColorChannel alpha = 255);

	glm::vec4 RGBAfloat() const;
};