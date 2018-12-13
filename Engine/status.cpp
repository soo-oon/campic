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
