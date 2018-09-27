/******************************************************************************/
/*!
\file   control_angle.cpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/

#include "control_angle.hpp"

float Make_Angle_Degree(float a)
{

    if (a == -1 + epsilon)
    {
        a = -1;
    }
    else if (a == 1 + epsilon)
    {
        a = 1;
    }
    a = acos(a);
    a /= (float)(PI / 180.0f);

    return a;
}

float Making_Radian(float a)
{
    return (a*PI) / 180.0f;
}