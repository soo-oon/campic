#include "State.hpp"
#include "JSON.hpp"
#include "status.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Sword.hpp"

void State::UpdateObjManager(float dt)
{
	objectmanager->Update(dt);
}

void State::Load()
{
	change_level.clear();
	level_change = false;
	objectmanager = std::make_unique<Objectmanager>();
	json = new JSON();
	sound = new Sound();
	sound->Initialize();
}

void State::UnLoad()
{
	objectmanager.release();
	objectmanager = nullptr;
	sound->Quit();
	delete json;
	delete sound;
}

void State::AddPlayer()
{
	objectmanager->AddObject("Player");
	objectmanager->FindObject("Player")->AddComponent(new Player());

	objectmanager->AddObject("Sword");
	objectmanager->FindObject("Sword")->AddComponent(new Sword(objectmanager->FindObject("Player").get()));
}

void State::SecondPlanForPlayer(Object* player)
{
}

void State::ChangeLevel(std::string ID)
{
	level_change = true;
	change_level = ID;
}
