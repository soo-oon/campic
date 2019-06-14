#include "Level.hpp"
#include "Input.hpp"
#include "UI.hpp"
#include "HUD_Level.hpp"
#include "Physics.hpp"
#include "Capture.hpp"

void Level::Initialize()
{
	AudioManager_.PlaySong("asset/sounds/Game_BGM.mp3");

	Physics_.SetNextLevel(false);

	camera = new Object();
	camera->SetObjectType(ObjectType::Camera);
	camera->AddComponent(new Camera("Level"));
	camera->GetComponentByTemplate<Camera>()->SetMinMaxSize(250);

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

	HUD_Level::ChangeCaptureLimit = false;


	///////////For PlayTest
}

void Level::Update(float dt)
{
	if (StateManager_.GetCurrentState()->GetCaptureLimit() <= 0)
		StateManager_.GetCurrentState()->GetCaptureLimit() = 0;

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
}
