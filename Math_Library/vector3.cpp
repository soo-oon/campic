/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  vector3.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "vector3.hpp"
#include <cmath>
#include "control_angle.hpp"

vector3 vector3::operator=(const vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

vector3 vector3::operator+(vector3& v) const
{
    vector3 result = *this;
    result += v;

    return result;
}

vector3& vector3::operator+=(vector3& v)
{
    x += v.x;
    y += v.y;
    z = +v.z;

    return *this;
}

vector3 vector3::operator-() const
{
    return vector3(-x, -y, -z);
}

vector3 vector3::operator-(vector3& v) const
{
    vector3 result = *this;
    result -= v;

    return result;
}

vector3& vector3::operator-=(vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

vector3 vector3::operator*(float s) const
{
    vector3 result = *this;
    result *= s;

    return result;
}

vector3 vector3::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

vector3 operator*(float s, vector3 v)
{
    return v * s;
}

vector3 vector3::operator/(float s) const
{
    vector3 result = *this;
    result /= s;

    return result;
}

vector3& vector3::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;

    return *this;
}


bool vector3::operator==(const vector3 v) const
{
    return x == v.x && y == v.y && z == v.z;
}

bool vector3::operator!=(const vector3 v)const
{
    return !(*this == v);
}

float dot(vector3& v1, vector3 v2)
{
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

vector3 cross_product(vector3 v1, vector3 v2)
{
    vector3 v3;

    v3.x = v1.y*v2.z - v1.z*v2.y;
    v3.y = v1.z*v2.x - v1.x*v2.z;
    v3.z = v1.x*v2.y - v1.y*v2.x;

    return v3;
}

vector3 normalize(vector3 v)
{
    vector3 u = sqrt(dot(v, v));

    return vector3((v.x / u.x), (v.y / u.y), (v.z / u.z));
}

float magnitude(vector3 v)
{
    return sqrt(dot(v, v));
}

float magnitude_squared(vector3 v)
{
    return dot(v, v);
}

float distance_between(vector3 v1, vector3 v2)
{
    vector3 v3= v2 - v1;

    return sqrt(dot(v3, v3));
}

float distance_between_squared(vector3 v1, vector3 v2)
{
    vector3 v3 = v2 - v1;

    return dot(v3, v3);
}


float Angle_Between_Vector(vector3 v1, vector3 v2)
{
    float a = dot(v1, v2) / (magnitude(v1)*magnitude(v2));

    return Make_Angle_Degree(a);
}
