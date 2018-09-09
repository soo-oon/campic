/******************************************************************************/
/*!
\file   vector3.cpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/

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

vector3 vector3::operator+(const vector3& v) const
{
    vector3 result = *this;
    result += v;

    return result;
}

vector3& vector3::operator+=(const vector3& v)
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

vector3 vector3::operator-(const vector3& v) const
{
    vector3 result = *this;
    result -= v;

    return result;
}

vector3& vector3::operator-=(const vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

vector3 vector3::operator*(const float s) const
{
    vector3 result = *this;
    result *= s;

    return result;
}

vector3 vector3::operator*=(const float s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

vector3 operator*(const float s, const vector3 v)
{
    return v * s;
}

vector3 vector3::operator/(const float s) const
{
    vector3 result = *this;
    result /= s;

    return result;
}

vector3& vector3::operator/=(const float s)
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

float dot(const vector3& v1, const vector3 v2)
{
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

vector3 cross_product(const vector3 v1, const vector3 v2)
{
    vector3 v3;

    v3.x = v1.y*v2.z - v1.z*v2.y;
    v3.y = v1.z*v2.x - v1.x*v2.z;
    v3.z = v1.x*v2.y - v1.y*v2.x;

    return v3;
}

vector3 normalize(const vector3 v)
{
    vector3 u = sqrt(dot(v, v));

    return vector3((v.x / u.x), (v.y / u.y), (v.z / u.z));
}

float magnitude(const vector3 v)
{
    return sqrt(dot(v, v));
}

float magnitude_squared(const vector3 v)
{
    return dot(v, v);
}

float distance_between(const vector3 v1, const vector3 v2)
{
    vector3 v3= v2 - v1;

    return sqrt(dot(v3, v3));
}

float distance_between_squared(const vector3 v1, const vector3 v2)
{
    vector3 v3 = v2 - v1;

    return dot(v3, v3);
}


float Angle_Between_Vector(const vector3 v1, const vector3 v2)
{
    float a = dot(v1, v2) / (magnitude(v1)*magnitude(v2));

    return Make_Angle_Degree(a);
}
