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
	background->AddComponent(new Animation("asset/images/Page/BackgroundAfernoon.png", "afternoon", 16, 0.15f, true));
	background->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Page/BackgroundDay.png", "day", 16, 0.15f, true);
	background->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Page/BackgroundNight.png", "night", 16, 0.15f, true);
	background->SetDepth(0.98f);
	background->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width+100), static_cast<float>(Application_.GetGLFWvidmode()->height+100)});

	switch (GetChapter().first)
	{
	case 1:
	{
		background->GetComponentByTemplate<Animation>()->ChangeAnimation("afternoon");
		break;
	}
	case 2:
	{
		background->GetComponentByTemplate<Animation>()->ChangeAnimation("day");
		break;
	}
	case 3:
	{
		background->GetComponentByTemplate<Animation>()->ChangeAnimation("night");
		break;
	}
	default:
		break;
	}
	
	Objectmanager_.AddObject(camera);
	Objectmanager_.AddObject(background);
}

void Level::Update(float dt)
{


	//background->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });

	//if (camera != nullptr)
	//{
	//	background->SetTranslation(camera->GetComponentByTemplate<Camera>()->GetCenter());
	//}
#ifdef _DEBUG
    std::cout << "(" << Input::GetMousePos().x << ", " << Input::GetMousePos().y << ")" << std::endl;
#else 
#endif
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

	if(Input::IsKeyTriggered(GLFW_KEY_F1))
	{
		GetCaptureLimit() += 10;
	}
}

void Level::ShutDown()
{
	UnLoad();
}
