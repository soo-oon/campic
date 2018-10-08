/******************************************************************************/
/*!
\file   affine2d.hpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/

#pragma once

#include "vector3.hpp"
#include "vector2.hpp"

struct affine2d
{
    float affine[3][3] = { { 0 } };

    affine2d() = default;
    affine2d(vector3 column1, vector3 column2, vector3 column3)
    {
        affine[0][0] = column1.x;
        affine[0][1] = column2.x;
        affine[0][2] = column3.x;
        affine[1][0] = column1.y;
        affine[1][1] = column2.y;
        affine[1][2] = column3.y;
        affine[2][0] = column1.z;
        affine[2][1] = column2.z;
        affine[2][2] = column3.z;
    }
    affine2d(float c0r0, float c0r1, float c0r2, float c1r0, float c1r1,
        float c1r2, float c2r0, float c2r1, float c2r2)
        : affine2d(vector3(c0r0, c1r0,  c2r0) , vector3(c0r1, c1r1, c2r1) , vector3(c0r2, c1r2, c2r2))
    {}

    affine2d operator*(affine2d a)const;
    affine2d operator*=(affine2d a);

    vector3 operator*(vector3 v)const;
    vector3 operator*=(vector3 v);

    vector2 operator*(vector2&& v)const;


    float operator()(int column, int row)const;
    float& operator()(int column, int row);
};
affine2d transpose(affine2d a);
affine2d rotation_affine(float degree);
affine2d build_identity_affine();
affine2d uniform_scale_affine(float a);
affine2d nonuniform_scale_affine(float a, float b);
affine2d build_translation(float a, float b);