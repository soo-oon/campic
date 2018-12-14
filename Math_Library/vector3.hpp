/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  vector3.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
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