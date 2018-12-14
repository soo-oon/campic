/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  control_angle.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#pragma once

#include <cmath>
#include <limits>

const float PI = 4.0f * std::atan(1.0f);
const float epsilon = std::numeric_limits<float>::epsilon();


float Make_Angle_Degree(float a);

float Making_Radian(float a);