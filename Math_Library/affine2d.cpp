/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: affine2d.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#include "affine2d.hpp"
#include <cassert>
#include "control_angle.hpp"

affine2d affine2d::operator*(affine2d a) const
{
    affine2d c;

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                c.affine[i][j] += this->affine[i][k] * a.affine[k][j];
            }
        }
    }

    return c;
}

affine2d affine2d::operator*=(affine2d a)
{
    affine2d c = *this * a;

    *this = c;

    return *this;
}

vector3 affine2d::operator*(vector3 v) const
{
    vector3 v2;

    v2.x = this->affine[0][0] * v.x + this->affine[0][1] * v.y
        + this->affine[0][2] * v.z;

    v2.y = this->affine[1][0] * v.x + this->affine[1][1] * v.y
        + this->affine[1][2] * v.z;

    v2.z = this->affine[2][0] * v.x + this->affine[2][1] * v.y
        + this->affine[2][2] * v.z;

    return v2;
}

vector3 affine2d::operator*=(vector3 v)
{
    vector3 v2;

    v2.x = this->affine[0][0] * v.x + this->affine[0][1] * v.y
        + this->affine[0][2] * v.z;

    v2.y = this->affine[1][0] * v.x + this->affine[1][1] * v.y
        + this->affine[1][2] * v.z;

    v2.z = this->affine[2][0] * v.x + this->affine[2][1] * v.y
        + this->affine[2][2] * v.z;

    return v2;
}

float affine2d::operator()(int column, int row) const
{
    assert(column >= 0 && column < 3);
    assert(row >= 0 && row < 3);

    float element;

    element = affine[column][row];

    return element;
}

float& affine2d::operator()(int column, int row)
{
    assert(column >= 0 && column < 3);
    assert(row >= 0 && row < 3);

    return affine[column][row];
}

vector2 affine2d::operator*(vector2&& v) const
{
    vector2 v2;

    v2.x = this->affine[0][0] * v.x + this->affine[0][1] * v.y
        + this->affine[0][2];

    v2.y = this->affine[1][0] * v.x + this->affine[1][1] * v.y
        + this->affine[1][2];

    return v2;
}
vector2 affine2d::operator*(vector2 v) const
{
	vector2 v2;

	v2.x = this->affine[0][0] * v.x + this->affine[0][1] * v.y
		+ this->affine[0][2];

	v2.y = this->affine[1][0] * v.x + this->affine[1][1] * v.y
		+ this->affine[1][2];

	return v2;
}
affine2d transpose(affine2d a)
{
    affine2d c;

    vector3 v1 = { a.affine[0][0] , a.affine[0][1], a.affine[0][2] };
    vector3 v2 = { a.affine[1][0] , a.affine[1][1], a.affine[1][2] };
    vector3 v3 = { a.affine[2][0] , a.affine[2][1], a.affine[2][2] };

    c.affine[0][0] = v1.x;
    c.affine[1][0] = v1.y;
    c.affine[2][0] = v1.z;
    
    c.affine[0][1] = v2.x;
    c.affine[1][1] = v2.y;
    c.affine[2][1] = v2.z;

    c.affine[0][2] = v3.x;
    c.affine[1][2] = v3.y;
    c.affine[2][2] = v3.z;

    return c;
}

affine2d rotation_affine(float degree)
{
    affine2d c;

    float cos_value = cos(Making_Radian(degree));
    float sin_value = sin(Making_Radian(degree));

    c.affine[0][0] = cos_value;
    c.affine[0][1] = -sin_value;
    c.affine[0][2] = 0.0f;

    c.affine[1][0] = sin_value;
    c.affine[1][1] = cos_value;
    c.affine[1][2] = 0.0f;

    c.affine[2][0] = 0.0f;
    c.affine[2][1] = 0.0f;
    c.affine[2][2] = 1.0f;

    return c;
}

affine2d build_identity_affine()
{
    affine2d c;

    c.affine[0][0] = 1.0f;
    c.affine[0][1] = 0.0f;
    c.affine[0][2] = 0.0f;

    c.affine[1][0] = 0.0f;
    c.affine[1][1] = 1.0f;
    c.affine[1][2] = 0.0f;

    c.affine[2][0] = 0.0f;
    c.affine[2][1] = 0.0f;
    c.affine[2][2] = 1.0f;

    return c;
}


affine2d uniform_scale_affine(float a)
{
    affine2d c;

    c.affine[0][0] = a;
    c.affine[0][1] = 0.0f;
    c.affine[0][2] = 0.0f;

    c.affine[1][0] = 0.0f;
    c.affine[1][1] = a;
    c.affine[1][2] = 0.0f;

    c.affine[2][0] = 0.0f;
    c.affine[2][1] = 0.0f;
    c.affine[2][2] = 1.0f;

    return c;
}

affine2d nonuniform_scale_affine(float a, float b)
{
    affine2d c;

    c.affine[0][0] = a;
    c.affine[0][1] = 0.0f;
    c.affine[0][2] = 0.0f;

    c.affine[1][0] = 0.0f;
    c.affine[1][1] = b;
    c.affine[1][2] = 0.0f;

    c.affine[2][0] = 0.0f;
    c.affine[2][1] = 0.0f;
    c.affine[2][2] = 1.0f;

    return c;
}

affine2d build_translation(float a, float b)
{
    affine2d c;

    c.affine[0][0] = 1;
    c.affine[0][1] = 0;
    c.affine[0][2] = a;
    c.affine[1][0] = 0;
    c.affine[1][1] = 1;
    c.affine[1][2] = b;
    c.affine[2][0] = 0;
    c.affine[2][1] = 0;
    c.affine[2][2] = 1;

    return c;
}
