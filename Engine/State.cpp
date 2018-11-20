#include "State.hpp"

void State::Load()
{
	level_change = false;
	objectmanager = new Objectmanager();
	world_physics = new WorldPhysics();
}

void State::UpdateObjManager(float dt)
{
	objectmanager->Update(dt);
}

void State::UnLoad()
{
	change_level.clear();
	delete objectmanager;
	delete world_physics;
}

void State::ChangeLevel(std::string ID)
{
	level_change = true;
	change_level = ID;
}
