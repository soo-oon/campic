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
#include "Player.hpp"
#include "Objectmanager.hpp"

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

void State::ChangeLevel(std::string ID)
{
	level_change = true;
	change_level = ID;

	if(ID == "Boss")
		AudioManager_.PlaySong("asset/sounds/bgm.mp3");
}

void State::Load()
{
    if (Objectmanager_.GetObjectMap().empty())
    {
        AddPlayer();
        AddSword();
    }

	AudioManager_.LoadSong("asset/sounds/bgm.mp3");
	AudioManager_.LoadSong("asset/sounds/plaid.mp3");

	AudioManager_.PlaySong("asset/sounds/plaid.mp3");

    if(m_player == nullptr)
    {
        //for(auto player : Objectmanager_.GetObjectMap())
        //{
        //    if(player->GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player)
        //    {
        //        m_player = player.get();
        //    }
        //}

    }
}

void State::AddPlayer()
{
	Object* player = new Object();
	player->AddComponent(new Player());

	Objectmanager_.AddObject(player);
	m_player = Objectmanager_.GetObjectMap()[Objectmanager_.GetObjectMap().size() - 1].get();
}

void State::AddSword()
{
    Object* sword = new Object();
    //sword->AddComponent(new Sword(Objectmanager_.GetObjectMap()[0].get()));

    Objectmanager_.AddObject(sword);
}


void State::UnLoad()
{
	Objectmanager_.RemoveObject();
}
