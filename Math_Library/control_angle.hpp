/******************************************************************************/
/*!
\file   control_angle.hpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/

#pragma once

#include <cmath>
#include <limits>

const float PI = 4.0f * std::atan(1.0f);
const float epsilon = std::numeric_limits<float>::epsilon();


float Make_Angle_Degree(float a);

float Making_Radian(float a);