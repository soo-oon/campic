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
#include "Capture.hpp"
#include <iostream>

void State::ChangeLevel(std::string ID)
{
	if (player_obj != nullptr)
		player_obj = nullptr;

	if (capture_obj != nullptr)
		capture_obj = nullptr;

	level_change = true;
	change_level = ID;
}

void State::BackToMenu()
{
	if (player_obj != nullptr)
		player_obj = nullptr;

	if (capture_obj != nullptr)
		capture_obj = nullptr;

	back_to_menu = true;
	change_level = "LevelSelector";
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
	JSON_.GetObjectDocument().SetObject();
	for(auto& i : Tile_Map_.GetGraphicsTiles())
	{
		JSON_.TilesToDocument(i.first, i.second, Tile_Type::Graphical, level_indicator + "/");
	}
	JSON_.GetTileDocument().SetObject();
	for (auto& i : Tile_Map_.GetPhysicalTiles())
	{
		JSON_.TilesToDocument(i.first,i.second, Tile_Type::Physical, level_indicator+"/");
	}
	JSON_.GetTileDocument().SetObject();
}

void State::UnLoad()
{
	if (player_obj != nullptr)
		player_obj = nullptr;

	if (capture_obj != nullptr)
		capture_obj = nullptr;

	Objectmanager_.RemoveObject();
	Tile_Map_.RemoveTiles();
}

void State::CreateCaptureCamera()
{
    Object* player_camera = new Object();
	player_camera->SetTranslation(start_pos);
    player_camera->SetScale({450,250});
    player_camera->SetDepth(-0.17f);
    player_camera->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    player_camera->SetObjectType(ObjectType::Capture_Camera_main);
	player_camera->AddComponent(new Sprite("asset/images/Objects/Capture.png"));
    player_camera->AddInitComponent(new Capture(StateManager_.GetCurrentState()->GetStartPosition()));

    Objectmanager_.AddObject(player_camera);
    Objectmanager_.SetCaptureObject(player_camera);
}

void State::CreatePlayer()
{
    Object* player = new Object();
    player->SetTranslation(start_pos);
	player->AddInitComponent(new Player());

    Objectmanager_.AddObject(player);
    Objectmanager_.SetPlayer(player);
}
