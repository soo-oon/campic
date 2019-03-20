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

void level2::Initialize()
{
	player_camera = new Object();
	player_camera->SetScale({ 508.0f, 354.0f });
	player_camera->SetMesh(mesh::CreateBox(1, Colors::Red));
	player_camera->SetObjectType(ObjectType::None);
	player_camera->AddComponent(new Sprite("asset/images/camera_frame.png"));
	player_camera->AddComponent(new Capture());
	SetPlayerPointer(player_camera);
	
    temp = new Object();
    temp->SetTranslation({ 100,-150 });
    temp->SetScale({ 50.0f, 50.0f });
    temp->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
    temp->SetDepth(0.0f);
    temp->AddComponent(new RigidBody());
    temp->AddComponent(new Collision(box_));
    temp->SetObjectType(ObjectType::None);
    temp->AddComponent(new Animation("asset/images/Enemies/1_Right.png", "rigsdfsfht", 5, 0.2f, true));
    //temp->AddComponent(new Enemy(MoveType::straight));


    cannon = new Object();
    cannon->SetTranslation({ 100,0 });
    cannon->SetScale({ 50.0f, 50.0f });
    cannon->SetMesh(mesh::CreateBox(1, { 0,0,255, 255 }));
    cannon->SetDepth(0.0f);
    cannon->AddComponent(new RigidBody());
    cannon->AddComponent(new Collision(box_));
    cannon->SetObjectType(ObjectType::Item_Static);
    cannon->AddComponent(new Projectile(Projectile_Type::Cannon));
    /*wall = new Object();
    wall->SetTranslation({ 100,-300 });
    wall->SetScale({ 50.0f, 20.0f });
    wall->SetMesh(mesh::CreateBox(1, { 255,255,0, 255 }));
    wall->SetDepth(0.0f);
    wall->SetObjectType(ObjectType::Wall);
    wall->AddComponent(new Collision(box_));
	Object* camera = new Object();
	camera->AddComponent(new Camera(this));


    int w, h;
    glfwGetWindowSize(Application_.GetWindow(), &w, &h);

    Object * background = new Object();
    background->SetTranslation({ 0,0 });
    background->SetScale(vector2(static_cast<float>(w), static_cast<float>(h)));
    background->SetMesh(mesh::CreateBox(1,{100,100,255}));
    background->SetDepth(0.9f);
	background->SetObjectType(ObjectType::Background);
    background->AddComponent(new Sprite("asset/images/background1.png"));*/
    
	obj.push_back(temp);
	//obj.push_back(camera);
	//obj.push_back(wall);
	//obj.push_back(background);
        obj.push_back(cannon);
	obj.push_back(player_camera);

	for(auto i : obj)
	{
		Objectmanager_.AddObject(i);
	}
}

void level2::Update(float dt)
{	

    if (!temp)
        std::cout << " noeno" << std::endl;
    if (Input::IsKeyTriggered(GLFW_KEY_D))
    {
        temp->GetComponentByTemplate<RigidBody>()->SetVelocity({50, 0});
    }
    if (Input::IsKeyTriggered(GLFW_KEY_S))
    {
        temp->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0, -50 });
    }
    if (Input::IsKeyTriggered(GLFW_KEY_W))
    {
        temp->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0,100});
    }
    if (Input::IsKeyTriggered(GLFW_KEY_A))
    {
        temp->GetComponentByTemplate<RigidBody>()->SetVelocity({ -50, 0 });
    }
    if (Input::IsKeyTriggered(GLFW_KEY_L))
    {
        Object* missile = new Object;
        missile->SetTranslation({ cannon->GetTransform().GetTranslation() });
        missile->SetScale({ 50.0f, 50.0f });
        missile->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
        missile->AddInitComponent(new RigidBody());
        missile->AddInitComponent(new Collision(box_));
        missile->SetObjectType(ObjectType::None);
        missile->AddInitComponent(new Sprite("asset/images/sword.png"));
        missile->GetComponentByTemplate<RigidBody>()->SetVelocity({ 10,10 });
        Objectmanager_.AddObject(missile);
        std::cout << Objectmanager_.GetObjectMap().size() << std::endl;
    }
    if (Input::IsKeyTriggered(GLFW_KEY_O))
    {
        if (!Tile_Map_.GetSpecificTile({ 2000,2000 }))
            std::cout << " null " << std::endl;
        else
            std::cout << " is existed " << std::endl;
    }

	if (Input::IsKeyTriggered(GLFW_KEY_R))
	{
		ChangeLevel("remake");
	}

	if (Input::IsKeyTriggered(GLFW_KEY_F1))
	{
		for (auto& obj : Objectmanager_.GetObjectMap())
		{
			JSON_.ObjectsToDocument(obj.get());
		}
		
		for (auto& tiles : Tile_Map_.GetGraphicsTiles())
		{
			JSON_.TilesToDocument(tiles.first, tiles.second, Tile_Type::Graphical);
		}
		
		std::cout << "Objects and Tiles Saved" << std::endl;
	}

	if (Input::IsKeyTriggered(GLFW_KEY_F2))
	{
		JSON_.LoadTilesFromJson(Tile_Type::Graphical);
		JSON_.LoadObjectFromJson();

		std::cout << "Objects and Tiles Loaded" << std::endl;
	}

	if (Input::IsKeyTriggered(GLFW_KEY_I))
		Tile_Map_.Delete_Tile();

    

}

void level2::ShutDown()
{
	obj.clear();
	UnLoad();
}
