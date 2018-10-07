#pragma once
#include "Objectmanager.hpp"
class WorldPhysics
{
public:
	void Movement(Object& object_name);
	void Movement_by_key(Object& object_name);
private:
	float gravity = 0;
	Objectmanager* object_manager;
	Object object;
};
