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
	LoadLevel();

    Object* temp = new Object();
    temp->SetTranslation({ -600,-230 });
    temp->SetScale({ 50.0f, 50.0f });
    temp->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
    temp->SetDepth(-0.5f);
    temp->SetObjectType(ObjectType::Player);
    temp->AddInitComponent(new RigidBody());
    temp->AddInitComponent(new Collision(box_));
    temp->AddInitComponent(new Animation("asset/images/Enemies/1_Right.png", "player", 5, 0.2f, true));
    SetPlayerPosition(temp->GetTransform().GetTranslation());

	player_camera = new Object();
	player_camera->SetScale({ 300.0f, 175.0f });
	player_camera->SetDepth(-0.2f);
	player_camera->SetMesh(mesh::CreateBox(1, {255,255,255,255}));
	player_camera->SetObjectType(ObjectType::None);
	player_camera->AddComponent(new Animation("asset/images/camera_frame.png", "basic_camera", 2, 0.5, true));
	player_camera->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/cheese.png", "cheese", 2, 0.5, true);
	player_camera->AddComponent(new Capture(GetPlayerPosition()));

	Object* camera = new Object();
	camera->SetObjectType(ObjectType::Camera);
	camera->AddComponent(new Camera("Level2"));
	

	Object* cannon = new Object();
	cannon->SetTranslation({ 480,-150 });
	cannon->SetScale({ 150,150 });
	cannon->SetObjectType(ObjectType::Item_Static);
	cannon->SetMesh(mesh::CreateBox());
	cannon->AddComponent(new Collision(box_));
	cannon->AddComponent(new Animation("asset/images/cannon.png", "cannon_standing", 5, 0.4f, true));
	cannon->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/cannon_fire.png", "cannon_fire", 6, 0.1, false);
	cannon->AddComponent(new Projectile(4.0f, 10.0f, Projectile_Type::Cannon));
	cannon->GetComponentByTemplate<Projectile>()->SetFireDir({ 350, 0 });

	Object* weapon = new Object();
	weapon->SetTranslation({ 30 , -235 });
	weapon->SetScale({ 100, 50 });
	weapon->SetObjectType(ObjectType::Item_Dynamic);
	weapon->SetMesh(mesh::CreateBox());
	weapon->AddComponent(new Sprite("asset/images/weapon.png"));
	weapon->AddComponent(new Collision(box_));
	weapon->AddComponent(new Projectile(1.0f, 3.0f, Projectile_Type::Weapon));
	weapon->GetComponentByTemplate<Projectile>()->SetFireDir({ 1000, 0 });

	obj.push_back(temp);
	obj.push_back(camera);
	obj.push_back(player_camera);
	obj.push_back(cannon);
	obj.push_back(weapon);


	for(auto i : obj)
	{
		Objectmanager_.AddObject(i);
	}
}

void level2::Update(float dt)
{	

	obj[1]->GetComponentByTemplate<Camera>()->SetCenter(obj[0]->GetTransform().GetTranslation());
	camera_center = obj[1]->GetComponentByTemplate<Camera>()->GetCenter();

	if (Input::IsKeyTriggered(GLFW_KEY_R))
	{
		ChangeLevel("Level2");
	}
}

void level2::ShutDown()
{
	obj.clear();
	UnLoad();
}
