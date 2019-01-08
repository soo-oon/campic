/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: State.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "State.hpp"
#include "JSON.hpp"
#include "status.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Sword.hpp"

//void State::UpdateObjManager(float dt)
//{
//	objectmanager->Update(dt);
//}
//
//void State::UpdateJsonState(StateManager* current)
//{
//	json->UpdateState(current);
//}

//void State::Load()
//{
//	change_level.clear();
//	level_change = false;
//	objectmanager = std::make_unique<Objectmanager>();
//	json = new JSON();
//	json->LoadLevelDocument();
//
//	sound = new Sound();
//	sound->Initialize();
//}
//
//void State::UnLoad()
//{
//	json->SaveAtEachDocument();
//	objectmanager.release();
//	objectmanager = nullptr;
//	sound->Quit();
//	delete sound;
//	delete json;
//}

//void State::AddPlayer()
//{
//	objectmanager->AddObject("Player");
//	objectmanager->FindObject("Player")->AddComponent(new Player());
//
//	objectmanager->AddObject("Sword");
//	objectmanager->FindObject("Sword")->AddComponent(new Sword(objectmanager->FindObject("Player").get()));
//}
//
//void State::SecondPlanForPlayer(Object* player)
//{
//}

void State::ChangeLevel(std::string ID)
{
	level_change = true;
	change_level = ID;
}
