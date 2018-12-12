#include "State.hpp"
#include "JSON.hpp"

void State::Load()
{
	level_change = false;
	objectmanager = new Objectmanager();
	json = new JSON();
	sound = new Sound();
	sound->Initialize();
}

void State::UpdateObjManager(float dt)
{
	objectmanager->Update(dt);
}

void State::UnLoad()
{
	change_level.clear();
	delete objectmanager;
	delete json;
	delete sound;
}

void State::ChangeLevel(std::string ID)
{
	level_change = true;
	change_level = ID;
}
