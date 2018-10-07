#pragma once
#include "vector2.hpp"
#include "Objectmanager.hpp"
class WorldPhysics
{
public:
	void Movement(std::string object_name);
private:
	float gravity = 0;
	Objectmanager object_manager;
};
