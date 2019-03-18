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
#include "Status.hpp"

void State::ChangeLevel(std::string ID)
{
	level_change = true;
	change_level = ID;

	if(ID == "Boss")
		AudioManager_.PlaySong("asset/sounds/bgm.mp3");
}

void State::Load()
{
 
}


void State::UnLoad()
{
	Objectmanager_.RemoveObject();
}
