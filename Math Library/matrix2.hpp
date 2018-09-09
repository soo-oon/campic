/******************************************************************************/
/*!
\file   matrix2.hpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/

#pragma once

#include "vector2.hpp"

struct matrix2
{
    matrix2() = default;

    matrix2(vector2 column1, vector2 column2)
    {
        matrix[0][0] = column1.x;
        matrix[0][1] = column2.x;
        matrix[1][0] = column1.y;
        matrix[1][1] = column2.y;
    }
    matrix2(float c0r0, float c0r1, float c1r0, float c1r1)
        :matrix2(vector2(c0r0, c1r0) , vector2(c0r1, c1r1))
    {}

    float matrix[2][2] = { {0}};

    matrix2& operator=(const matrix2& m);

    matrix2 operator*(matrix2 m) const;
    matrix2& operator*=(matrix2 m);

    matrix2 operator-(matrix2& m)const;

    matrix2 operator*(float a) const;
    matrix2& operator*=(float a);
    friend matrix2 operator*(float a, matrix2 m);
    
    vector2 operator*(vector2 v) const;

    bool operator==(const matrix2 m) const;

    float operator()(int column, int row) const;
    float& operator()(int column, int row);

};
matrix2 transpose(matrix2 m);
matrix2 rotation(float degree);
matrix2 build_identity();
float determinate(matrix2 m);
matrix2 inverse_matrix(matrix2 m);
matrix2 uniform_scale_matrix(float a);
matrix2 nonuniform_scale_matrix(float a, float b);