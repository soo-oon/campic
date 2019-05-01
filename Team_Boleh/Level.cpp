#include "Level.hpp"
#include "Input.hpp"
#include "UI.hpp"
#include <iostream>

void Level::Initialize()
{
	AudioManager_.PlaySong("asset/sounds/Game_BGM.mp3");

	camera = new Object();
	camera->SetObjectType(ObjectType::Camera);
	camera->AddComponent(new Camera("Level"));

	background = new Object();
	background->SetMesh(mesh::CreateBox());
	background->SetObjectType(ObjectType::Background);
	background->AddComponent(new Animation("asset/images/UI/BackgroundSunSet.png", "BackGround", 16, 0.15f, true));
	background->SetDepth(0.98f);
	background->SetScale((Application_.GetScreenSize().x + 100, Application_.GetScreenSize().y+100));

	Objectmanager_.AddObject(camera);
	Objectmanager_.AddObject(background);
}

void Level::Update(float dt)
{
	background->SetScale(Application_.GetScreenSize() + 100);

	if (camera != nullptr)
	{
		background->SetTranslation(camera->GetComponentByTemplate<Camera>()->GetCenter());
	}

    if(camera->GetObjectType() != ObjectType::Camera)
    {
        for(auto i : Objectmanager_.GetObjectMap())
        {
            if (i.get()->GetObjectType() == ObjectType::Camera)
            {
                camera = i.get();
            }
        }
    }
    if(Input::IsKeyPressed(GLFW_KEY_UP))
    {
        camera->GetComponentByTemplate<Camera>()->MoveUp(6.f);
    }
    if (Input::IsKeyPressed(GLFW_KEY_DOWN))
    {
        camera->GetComponentByTemplate<Camera>()->MoveUp(-6.f);
    }
    if (Input::IsKeyPressed(GLFW_KEY_LEFT))
    {
        camera->GetComponentByTemplate<Camera>()->MoveRight(-6.f);
    }
    if (Input::IsKeyPressed(GLFW_KEY_RIGHT))
    {
        camera->GetComponentByTemplate<Camera>()->MoveRight(6.f);
    }

	if (Input::IsKeyTriggered(GLFW_KEY_F2))
		BackToMenu();

	if(Input::IsKeyTriggered(GLFW_KEY_F1))
	{
		GetCaptureLimit() += 10;
	}

	if(Input::IsKeyTriggered(GLFW_KEY_F5))
	{
		UnLoad();
		StateManager_.ChangeStage();
	}
}

void Level::ShutDown()
{
	UnLoad();
}
