/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  level2.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jun Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "level2.hpp"
#include "Input.hpp"
#include "Animation.hpp"
#include <iostream>
#include "Particle_Generator.hpp"
#include "Camera.hpp"
#include "Font.hpp"
#include "Sound.hpp"
#include "Application.hpp"
#include "Tile_Map.hpp"
#include "Capture.hpp"
#include "Projectile.hpp"
#include "Player.hpp"

void level2::Initialize()
{
	//LoadLevel();

	Object* camera = new Object();
	camera->SetObjectType(ObjectType::Camera);
	camera->AddComponent(new Camera("Level2"));

	Objectmanager_.AddObject(camera);
}

void level2::Update(float dt)
{	
	if (Input::IsKeyTriggered(GLFW_KEY_R))
	{
		ChangeLevel("Level2");
	}

	if (Input::IsKeyTriggered(GLFW_KEY_I))
		Tile_Map_.Delete_Tile();
}

void level2::ShutDown()
{
	UnLoad();
}
