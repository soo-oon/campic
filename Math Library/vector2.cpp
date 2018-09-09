/******************************************************************************/
/*!
\file   vector2.cpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/

#include "vector2.hpp"
#include <cmath>
#include "control_angle.hpp"

vector2& vector2::operator=(const vector2& v)
{
    x = v.x;
    y = v.y;

    return *this;
}

vector2 vector2::operator+(const float a) const
{
    vector2 temp = *this;
    temp += a;
    return temp;
}

vector2& vector2::operator+=(const float a)
{
    x += a;
    y += a;

    return *this;
}

vector2 vector2::operator-(const float a) const
{
    vector2 temp = *this;
    temp -= a;
    return temp;
}

vector2& vector2::operator-=(const float a)
{
    x -= a;
    y -= a;

    return *this;
}

vector2 vector2::operator+(const vector2& v) const
{
    vector2 result = *this;
    result += v;

    return result;
}

vector2& vector2::operator+=(const vector2 v)
{
    x += v.x;
    y += v.y;

    return *this;
}

vector2 vector2::operator-() const
{
    return vector2(-x, -y);
}

vector2 vector2::operator-(const vector2& v) const
{
    vector2 result = *this;
    result -= v;

    return result;
}

vector2& vector2::operator-=(const vector2& v)
{
    x -= v.x;
    y -= v.y;

    return *this;
}

vector2 vector2::operator*(const float s) const
{
    vector2 temp = *this;

    temp.x *= s;
    temp.y *= s;

    return temp;
}

vector2& vector2::operator*=(const float s)
{
    x *= s;
    y *= s;

    return *this;
}

vector2 operator*(const float s, const vector2& v)
{
    return v * s;
}

vector2 vector2::operator/(const float s) const
{
    vector2 result = *this;
    result /= s;

    return result;
}

vector2& vector2::operator/=(const float s)
{
    x /= s;
    y /= s;

    return *this;
}

bool vector2::operator==(const vector2 v) const
{
    return x == v.x && y == v.y;
}

bool vector2::operator!=(const vector2 v) const
{
    return !(*this == v);
}

float dot(const vector2& v1, const vector2& v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}

vector2 perpendicular_to(const vector2& v)
{
    return vector2(-v.y, v.x);
}

vector2 normalize(const vector2 v)
{
    vector2 u = (float)sqrt(dot(v, v));

    return vector2((v.x / u.x),(v.y/u.y));
}

float magnitude(const vector2 v)
{
    return sqrt(dot(v, v));
}

float magnitude_squared(const vector2 v)
{
    return dot(v, v);
}   

float distance_between(const vector2 v1, const vector2 v2)
{
    vector2 v3 = v2 - v1;

    return sqrt(dot(v3, v3));
}

float distance_between_squared(const vector2 v1, const vector2 v2)
{
    vector2 v3 = v2 - v1;

    return dot(v3,v3);
}

float Angle_Between_Vector(const vector2 v1, const vector2 v2)
{
    float a = dot(v1, v2)/ (magnitude(v1)*magnitude(v2));

    return Make_Angle_Degree(a);
}
