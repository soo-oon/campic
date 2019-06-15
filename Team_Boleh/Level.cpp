/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Level.cpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : TaeWook Kang
Secondary :
- End Header ----------------------------------------------------------------*/
#include "Level.hpp"
#include "Input.hpp"
#include "UI.hpp"
#include "HUD_Level.hpp"
#include "Physics.hpp"
#include "Capture.hpp"
#include "HUD.hpp"

void Level::Initialize()
{
	switch(GetChapter().first)
	{
	case 1:
		{
		AudioManager_.PlaySong("asset/sounds/BGM_Day.mp3");
		break;
		}
	case 2:
	{
		AudioManager_.PlaySong("asset/sounds/BGM_Sunset.mp3");
		break;
	}
	case 3:
	{
		AudioManager_.PlaySong("asset/sounds/BGM_Night.mp3");
		break;
	}
	default:
		break;
	}

	Physics_.SetNextLevel(false);

	camera = new Object();
	camera->SetObjectType(ObjectType::Camera);
	camera->AddComponent(new Camera("Level"));
	camera->GetComponentByTemplate<Camera>()->SetMinMaxSize({150, 250});

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
		background->GetComponentByTemplate<Animation>()->ChangeAnimation("day");
		break;
	}
	case 2:
	{
		background->GetComponentByTemplate<Animation>()->ChangeAnimation("afternoon");
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

	std::cout << "obj : " << Objectmanager_.GetObjectMap().size() << std::endl;
	std::cout << "hud button: " << HUD_.Get_HUD_Button_Manager().size() << std::endl;
	std::cout << "hud obj : " << HUD_.Get_HUD_Object_Manager().size() << std::endl;
	std::cout << "g tile : " << Tile_Map_.GetGraphicsTiles().size() << std::endl;
	std::cout << "p tile : " << Tile_Map_.GetPhysicalTiles().size() << std::endl;

	HUD_Level::ChangeCaptureLimit = false;

}

void Level::Update(float dt)
{

	if(camera->GetComponentByTemplate<Camera>()->GetBaseObject() == nullptr)
	{
		if(auto player = StateManager_.GetCurrentState()->GetPlayerObjectPointer();
			player != nullptr)
		{
			camera->GetComponentByTemplate<Camera>()->SetBaseObject(player);
		}
	}

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

	if (Input::IsKeyTriggered(GLFW_KEY_R))
		StateManager_.ChangeStage();


#ifdef _DEBUG
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
#endif

	if(Input::IsKeyTriggered(GLFW_KEY_F1))
	{
		if(GetCaptureLimit() <= MAX_CAPTRUE_COUNT)
		{
			Capture::IsChangeCaptureCount = true;
			GetCaptureLimit() += 10;
		}
	}

    if(Input::IsKeyTriggered(GLFW_KEY_F5))
    {
        std::string a = GetLevelIndicator();

        std::string temp = a.substr(5, a.size());

        int b = std::atoi(temp.c_str());
        ++b;

        std::string lev = "Level";
        lev.append(std::to_string(b));

        if(b == 19)
        {
            StateManager_.ToEndScene();
        }
        else
        {
            SetLevelIndicator(lev);
            ChangeLevel(level_indicator);

            StateManager_.ChangeStage();
        }
    }

    if (Input::IsKeyTriggered(GLFW_KEY_F7))
    {
       StateManager_.ToEndScene();
    }
}

void Level::ShutDown()
{
	UnLoad();
	background = nullptr;
	m_door = nullptr;
	camera = nullptr;
}
