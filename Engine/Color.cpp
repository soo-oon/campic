#include "Color.hpp"

Color::Color(ColorChannel red, ColorChannel green, ColorChannel blue, ColorChannel alpha)
	:Red(red), Green(green), Blue(blue), Alpha(alpha)
{}

vector4 Color::RGBAfloat() const
{
	return { Red / 255.0f, Green / 255.0f, Blue / 255.0f, Alpha / 255.0f };
}