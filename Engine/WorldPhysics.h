#pragma once
#include "Objectmanager.hpp"

class WorldPhysics	// WorldPhysics have to collision check 
{					// It can move all stuff in level
public:
	void Movement(Object& object_name);
	void Movement_by_key(Object& object_name);
	void Gravity_on(Objectmanager* objectmanager_, float gravity = 1);
	void Movement_Velocity(Object& object_name);
private:
	Object object;
};
