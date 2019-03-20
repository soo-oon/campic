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

void State::ChangeLevel(std::string ID)
{
	level_change = true;
	change_level = ID;
}

void State::Load()
{
	//AudioManager_.LoadSong("asset/sounds/bgm.mp3");
	//AudioManager_.LoadSong("asset/sounds/plaid.mp3");
	//AudioManager_.PlaySong("asset/sounds/plaid.mp3");
}

void State::UnLoad()
{
	Objectmanager_.RemoveObject();
}
