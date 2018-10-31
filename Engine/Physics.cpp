#include "Physics.hpp"
#include "RigidBody.hpp"
#include "Collision.hpp"

bool Physics::Initialize()
{
	return true;
}

void Physics::PhysicsObjectUpdate(Objectmanager* objectmanager)
{
	temp_obj = objectmanager;
}

void Physics::Update(float dt)
{
	if (temp_obj != nullptr)
	{
		for (std::map<std::string, std::unique_ptr<Object>>::iterator it = temp_obj->GetObjectMap().begin();
			it != temp_obj->GetObjectMap().end(); ++it)
		{
			Object temp = *(it->second.get());

			if (temp.GetComponentByTemplate<RigidBody>() != nullptr)
			{
				temp.GetComponentByTemplate<RigidBody>()->Update(dt);
			}

			if (temp.GetComponentByTemplate<Collision>() != nullptr)
			{
				temp.GetComponentByTemplate<Collision>()->Update(dt);
			}
		}
	}
}


void Physics::Quit()
{
	temp_obj = nullptr;
}



