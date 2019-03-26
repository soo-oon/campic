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

    Object* temp = new Object();
    temp->SetTranslation({ -400,0 });
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
	cannon->SetTranslation({ 0,0 });
	cannon->SetScale({ 150,150 });
	cannon->SetObjectType(ObjectType::Item_Static);
	cannon->SetMesh(mesh::CreateBox());
	cannon->AddComponent(new Animation("asset/images/cannon.png", "cannon_standing", 5, 0.4f, true));
	cannon->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/cannon_fire.png", "cannon_fire", 6, 0.1, false);
	cannon->AddComponent(new Projectile(3.0f, 10.0f, Projectile_Type::Cannon));

	Object* weapon = new Object();
	weapon->SetTranslation({ 0 , -100 });
	weapon->SetScale({ 100, 50 });
	weapon->SetObjectType(ObjectType::Item_Static);
	weapon->SetMesh(mesh::CreateBox());
	weapon->AddComponent(new Sprite("asset/images/weapon.png"));
	weapon->AddComponent(new Collision(box_));
	weapon->AddComponent(new Projectile(0.0f, 3.0f, Projectile_Type::Weapon, temp));

 //   //temp->AddComponent(new Enemy(MoveType::straight));


 //   Object* cannon = new Object();
 //   cannon->SetTranslation({ 100,0 });
 //   cannon->SetScale({ 50.0f, 50.0f });
 //   cannon->SetMesh(mesh::CreateBox(1, { 0,0,255, 255 }));
 //   cannon->SetDepth(0.0f);
 //   cannon->AddComponent(new RigidBody());
 //   cannon->AddComponent(new Collision(box_));
 //   cannon->SetObjectType(ObjectType::Item_Static);
 //   cannon->AddComponent(new Projectile(Projectile_Type::Cannon));

 //   /*wall = new Object();
 //   wall->SetTranslation({ 100,-300 });
 //   wall->SetScale({ 50.0f, 20.0f });
 //   wall->SetMesh(mesh::CreateBox(1, { 255,255,0, 255 }));
 //   wall->SetDepth(0.0f);
 //   wall->SetObjectType(ObjectType::Wall);
 //   wall->AddComponent(new Collision(box_));
	//Object* camera = new Object();
	//camera->AddComponent(new Camera(this));


 //   int w, h;
 //   glfwGetWindowSize(Application_.GetWindow(), &w, &h);

 //   Object * background = new Object();
 //   background->SetTranslation({ 0,0 });
 //   background->SetScale(vector2(static_cast<float>(w), static_cast<float>(h)));
 //   background->SetMesh(mesh::CreateBox(1,{100,100,255}));
 //   background->SetDepth(0.9f);
	//background->SetObjectType(ObjectType::Background);
 //   background->AddComponent(new Sprite("asset/images/background1.png"));*/
 //   

	obj.push_back(temp);
	obj.push_back(camera);
	obj.push_back(player_camera);
	obj.push_back(cannon);
	obj.push_back(weapon);

	//obj.push_back(background);

	for(auto i : obj)
	{
		Objectmanager_.AddObject(i);
	}
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
	obj.clear();
	UnLoad();
}
