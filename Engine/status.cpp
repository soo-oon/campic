#include "status.hpp"

Status::Status(int Object_hp = 5, int object_damage = 1, float object_speed = 1)
{
	hp = Object_hp;
	damage = object_damage;
	move_speed = object_speed;
}

bool Status::Initialize(Object * Ob)
{
	object = Ob;
	return true;
}

void Status::Update(float dt)
{
	if (hp == 0)
		isLived = false;
}

void Status::Delete()
{
}
