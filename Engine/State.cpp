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

void State::LoadLevel()
{
	JSON_.LoadLevel(level_indicator + "/", level_indicator);
}

void State::LoadLevel(const std::string& current_level)
{
	JSON_.LoadLevel(current_level + "/", current_level);
}

void State::SaveLevel()
{
	for (auto& i : Objectmanager_.GetObjectMap())
	{
		JSON_.SaveLevelObject(i.get(),level_indicator + "/", level_indicator);
	}
	for(auto& i : Tile_Map_.GetGraphicsTiles())
	{
		JSON_.TilesToDocument(i.first, i.second, Tile_Type::Graphical, level_indicator + "/");
	}
	for (auto& i : Tile_Map_.GetPhysicalTiles())
	{
		JSON_.TilesToDocument(i.first,i.second, Tile_Type::Physical, level_indicator+"/");
	}
}

void State::UnLoad()
{
	Objectmanager_.RemoveObject();
}
