/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  control_angle.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#include "control_angle.hpp"

float To_Degree(float a)
{
	a = (180.0f / PI)*a;

    return a;
}


float To_Radian(float a)
{
    return (a*PI) / 180.0f;
}

