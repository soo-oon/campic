/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : vector2.hpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : JinHyun Choi
Secondary :
- End Header ----------------------------------------------------------------*/

#pragma once
#include <ostream>

struct vector2
{
    vector2() = default;
    vector2(float a)
    {
        x = a;
        y = a;
    }
    vector2(float a, float b)
    {
        x = a;
        y = b;
    }

    vector2& operator=(const vector2 v);

    vector2 operator+(float a) const;
    vector2& operator+=(float a);

    vector2 operator-(float a) const;
    vector2& operator-=(float a);

    vector2 operator+(vector2 v) const;
    vector2& operator+=(vector2 v);

    vector2 operator-() const;
    vector2 operator-(vector2 v) const;
    vector2& operator-=(vector2& v);

    vector2 operator*(float s) const;
    vector2& operator*=(float s);

    vector2 operator/(float s)const;
    vector2& operator/=(float s);

    bool operator==(const vector2 v) const;
    bool operator!=(const vector2 v) const;

	friend std::ostream& operator<<(std::ostream& os, vector2 vector);

    float x = 0;
    float y = 0;
};
vector2 operator*(float s, const vector2& v);

float dot(vector2& v1, vector2& v2);

float dot(const vector2& v1, const vector2& v2);

vector2 perpendicular_to(vector2& v);

vector2 normalize(vector2 v);

float magnitude(vector2 v);

float magnitude_squared(vector2 v);

float distance_between(vector2 v1, vector2 v2);

float distance_between_squared(vector2 v1, vector2 v2);

float Angle_Between_Vector(vector2 v1, vector2 v2);