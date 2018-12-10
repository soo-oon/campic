#include "State.hpp"

void State::Load()
{
	level_change = false;
	objectmanager = new Objectmanager();
}

void State::UpdateObjManager(float dt)
{
	objectmanager->Update(dt);
}

void State::UnLoad()
{
	change_level.clear();
	delete objectmanager;
}

void State::ChangeLevel(std::string ID)
{
	level_change = true;
	change_level = ID;
}
