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
#include <iostream>
#include "Capture.hpp"

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
    player_camera->SetScale({ 300.0f, 175.0f });
    player_camera->SetDepth(-0.2f);
    player_camera->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    player_camera->SetObjectType(ObjectType::Capture_Camera_main);
    player_camera->AddInitComponent(new Animation("asset/images/camera_frame.png", "basic_camera", 2, 0.5, true));
    player_camera->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/cheese.png", "cheese", 2, 0.5, true);
    player_camera->AddInitComponent(new Capture(StateManager_.GetCurrentState()->GetStartPosition()));

    Objectmanager_.AddObject(player_camera);
    Objectmanager_.SetCaptureObject(player_camera);
}

void State::CreatePlayer()
{
    Object* player = new Object();
    player->SetTranslation(Input::GetMousePos());
    player->SetScale({ 80.0f, 80.f });
    player->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
    player->SetDepth(-0.5f);
    player->SetObjectType(ObjectType::Player);
	player->AddInitComponent(new Animation("asset/images/Player_Animation.png", "player", 8, 0.05f, true));
    player->AddInitComponent(new RigidBody());
    player->AddInitComponent(new Collision(box_));
	player->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Player_Capture.png", "capture", 4, 0.01f, false);
	player->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Player_Jump.png", "jump", 12, 0.01f, false);

    Objectmanager_.AddObject(player);
    Objectmanager_.SetPlayer(player);
}
