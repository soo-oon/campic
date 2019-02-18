#include "Status.hpp"

bool Status::Initialize(Object* Ob)
{
	if(object == nullptr)
	{
		object = Ob;
	}
	return true;
}

void Status::Update(float dt)
{
	if(hp <= 0)
		is_alive = false;
}

void Status::Delete()
{
	
}

void Status::SetObjectType(ObjectType obj_type)
{
    object_type = obj_type;
}

void Status::Damaged(int damage)
{
	hp -= damage;
}
