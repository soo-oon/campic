/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: status.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#include "status.hpp"

Status::Status(int Object_hp, int object_damage, float object_speed)
{
	hp = Object_hp;
	damage = object_damage;
	move_speed = object_speed;
}

bool Status::Initialize(Object * Ob)
{
	if (object == nullptr)
	{
		object = Ob;
	}
	return true;
}

void Status::Update(float dt)
{
	if (hp < 0)
		isLived = false;

}

void Status::Delete()
{
}

void Status::Damaged_hp(int damage_level)
{
	hp -= damage_level;
}
