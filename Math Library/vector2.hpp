/******************************************************************************/
/*!
\file   vector2.hpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/

#pragma once

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

    vector2& operator=(const vector2& v);

    vector2 operator+(const float a) const;
    vector2& operator+=(const float a);

    vector2 operator-(const float a) const;
    vector2& operator-=(const float a);

    vector2 operator+(const vector2& v) const;
    vector2& operator+=(const vector2 v);

    vector2 operator-() const;
    vector2 operator-(const vector2& v) const;
    vector2& operator-=(const vector2& v);

    vector2 operator*(const float s) const;
    vector2& operator*=(const float s);

    vector2 operator/(const float s)const;
    vector2& operator/=(const float s);

    bool operator==(const vector2 v) const;
    bool operator!=(const vector2 v) const;


    float x = 0;
    float y = 0;
};
vector2 operator*(float s, const vector2& v);

float dot(const vector2& v1, const vector2& v2);

vector2 perpendicular_to(const vector2& v);

vector2 normalize(const vector2 v);

float magnitude(const vector2 v);

float magnitude_squared(const vector2 v);

float distance_between(const vector2 v1, const vector2 v2);

float distance_between_squared(const vector2 v1, const vector2 v2);

float Angle_Between_Vector(const vector2 v1, const vector2 v2);