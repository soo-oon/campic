/******************************************************************************/
/*!
\file   vector3.hpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/

#pragma once

struct vector3
{
    vector3() = default;
    vector3(float a)
    {
        x = a;
        y = a;
        z = a;
    }

    vector3(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }

    vector3 operator=(const vector3& v);

    vector3 operator+(vector3& v)const;
    vector3& operator+=(vector3& v);

    vector3 operator-() const;
    vector3 operator-(vector3& v)const;
    vector3& operator-=(vector3& v);

    vector3 operator*(float s)const;
    vector3 operator*=(float s);
    friend vector3 operator*(float s, vector3 v);

    vector3 operator/(float s)const;
    vector3& operator/=(float s);

    bool operator ==(const vector3 v) const;
    bool operator !=(const vector3 v) const;



    float x = 0;
    float y = 0;
    float z = 0;
};

float dot(vector3& v1, vector3 v2);

vector3 cross_product(vector3 v1, vector3 v2);

vector3 normalize(vector3 v);

float magnitude(vector3 v);

float magnitude_squared(vector3 v);

float distance_between(vector3 v1, vector3 v2);

float distance_between_squared(vector3 v1, vector3 v2);

float Angle_Between_Vector(vector3 v1, vector3 v2);