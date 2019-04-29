#include "Level.hpp"
#include "Input.hpp"
#include "UI.hpp"
#include <iostream>

void Level::Initialize()
{
	camera = new Object();
	camera->SetObjectType(ObjectType::Camera);
	camera->AddComponent(new Camera("Level"));

	Objectmanager_.AddObject(camera);
}

void Level::Update(float dt)
{

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
        camera->GetComponentByTemplate<Camera>()->MoveUp(2.f);
    }
    if (Input::IsKeyPressed(GLFW_KEY_DOWN))
    {
        camera->GetComponentByTemplate<Camera>()->MoveUp(-2.f);
    }
    if (Input::IsKeyPressed(GLFW_KEY_LEFT))
    {
        camera->GetComponentByTemplate<Camera>()->MoveRight(-2.f);
    }
    if (Input::IsKeyPressed(GLFW_KEY_RIGHT))
    {
        camera->GetComponentByTemplate<Camera>()->MoveRight(2.f);
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
