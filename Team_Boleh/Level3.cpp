#include "Level3.hpp"
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

void Level3::Initialize()
{
	LoadLevel();

	OneWayObject = new Object();
	OneWayObject->SetScale({ 125.0f, 50.0f });
	OneWayObject->SetTranslation({ -136, -152 });
	OneWayObject->AddInitComponent(new RigidBody());
	OneWayObject->GetComponentByTemplate<RigidBody>()->SetGravity(0);
	OneWayObject->AddComponent(new MovingObject(2.0f, OneWayObject->GetTransform().GetTranslation(), 100.0f, Direction::RIGHT, MovementType::ONEWAY, 2.0f));
	OneWayObject->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	OneWayObject->AddInitComponent(new Collision());
	OneWayObject->AddInitComponent(new Sprite("asset/images/UI/StartButton.png"));
	container.push_back(OneWayObject);

	for (auto& i : container)
	{
		Objectmanager_.AddObject(i);
	}
}

void Level3::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_0))
		BackToMenu();
}

void Level3::ShutDown()
{
	UnLoad();
}
