/******************************************************************************/
/*!
\file   matrix2.cpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/

#include "matrix2.hpp"
#include <cassert>
#include "control_angle.hpp"

matrix2& matrix2::operator= (const matrix2& m)
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            matrix[i][j] = m.matrix[i][j];
        }
    }

    return *this;
}

matrix2 matrix2::operator*(matrix2 m) const
{
    matrix2 c;

    for (int i = 0; i<2; i++)
    {
        for (int j = 0; j<2; j++)
        {
            for (int k = 0; k<2; k++)
            {
                c.matrix[i][j] += m.matrix[i][k] * this->matrix[k][j];
            }
        }
    }

    return c;
}

matrix2& matrix2::operator*=(matrix2 m)
{
    matrix2 c = *this * m;

    *this = c;

    return *this;
}

matrix2 matrix2::operator-(matrix2& m) const
{
    matrix2 c;

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            c.matrix[i][j] = m.matrix[i][j] - matrix[i][j];
        }
    }

    return c;
}

matrix2 matrix2::operator*(float a) const
{
    matrix2 result = *this;
    result *= a;

    return result;
}

matrix2& matrix2::operator*=(float a)
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            matrix[i][j] *= a;
        }
    }

    return *this;
}

matrix2 operator*(float a, matrix2 m)
{
    return m * a;
}


vector2 matrix2::operator*(vector2 v) const
{
    vector2 temp;
        
    temp.x = matrix[0][0] * v.x + matrix[0][1] * v.y;
    temp.y = matrix[1][0] * v.x + matrix[1][1] * v.y;
        
    return temp;
}

bool matrix2::operator==(const matrix2 m) const
{
    int a = 0;

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            if(matrix[i][j] == m.matrix[i][j])
            {
                ++a;
            }
        }
    }

    return a == 4;
}


float matrix2::operator()(int column, int row) const
{
    assert(column >= 0 && column < 2);
    assert(row >= 0 && row < 2);

    float element;

    element =  matrix[column][row];

    return element;
}

float& matrix2::operator()(int column, int row)
{
    assert(column >= 0 && column < 2);
    assert(row >= 0 && row < 2);

    return matrix[column][row];
}

matrix2 transpose(matrix2 m)
{
    float temp;
    temp = m.matrix[0][1];

    m.matrix[0][1] = m.matrix[1][0];
    m.matrix[1][0] = temp;

    return m;
}

matrix2 rotation(float degree)
{
    matrix2 m;

    float cos_value = cos(Making_Radian(degree));
    float sin_value = sin(Making_Radian(degree));

    m.matrix[0][0] = cos_value;
    m.matrix[0][1] = -sin_value;
    m.matrix[1][0] = sin_value;
    m.matrix[1][1] = cos_value;

    return m;
}

matrix2 build_identity()
{
    matrix2 m;
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 0;
    m.matrix[1][0] = 0;
    m.matrix[1][1] = 1;

    return m;
}

float determinate(matrix2 m)
{
    float a = m.matrix[0][0] * m.matrix[1][1] - m.matrix[0][1] * m.matrix[1][0];

    assert(a != 0);

    return a;
}

matrix2 inverse_matrix(matrix2 m)
{
    float temp, a;

    temp = m.matrix[0][0];
    m.matrix[0][0] = m.matrix[1][1];
    m.matrix[1][1] = temp;
    m.matrix[0][1] = -m.matrix[0][1];
    m.matrix[1][0] = -m.matrix[1][0];

    a = (float)1.0 / determinate(m);

    return m*a;
}

matrix2 uniform_scale_matrix(float a)
{
    matrix2 m;

    m.matrix[0][0] = a;
    m.matrix[0][1] = 0.0f;
    m.matrix[1][0] = 0.0f;
    m.matrix[1][1] = a;

    return m;
}

matrix2 nonuniform_scale_matrix(float a, float b)
{
    matrix2 m;

    m.matrix[0][0] = a;
    m.matrix[0][1] = 0.0f;
    m.matrix[1][0] = 0.0f;
    m.matrix[1][1] = b;

    return m;
}
