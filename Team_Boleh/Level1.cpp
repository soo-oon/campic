#include "Level1.hpp"
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
#include "MovingObject.hpp"

void Level1::Initialize()
{
	LoadLevel();

	RoundObject = new Object();
	RoundObject->SetScale({ 125.0f, 50.0f });
	RoundObject->SetTranslation({ -136, -152 });
	RoundObject->AddInitComponent(new RigidBody());
	RoundObject->GetComponentByTemplate<RigidBody>()->SetGravity(0);
	RoundObject->AddComponent(new MovingObject(5.0f, RoundObject->GetTransform().GetTranslation(), 100.0f, Direction::DOWN, MovementType::ROUND, 0.0f));
	RoundObject->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	RoundObject->AddInitComponent(new Collision());
	//UpDownPlatform->SetObjectType(ObjectType::Item_Dynamic);
	RoundObject->AddInitComponent(new Sprite("asset/images/UI/StartButton.png"));
	container.push_back(RoundObject);

	for (auto& i : container)
	{
		Objectmanager_.AddObject(i);
	}
}

void Level1::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_R))
	{
		ChangeLevel("Level1");
	}

	if (Input::IsKeyTriggered(GLFW_KEY_I))
		Tile_Map_.Delete_Tile();
}

void Level1::ShutDown()
{
	UnLoad();
}
