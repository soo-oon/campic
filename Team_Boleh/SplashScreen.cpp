/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : SplashScreen.cpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : JinHyun Choi
Secondary :
- End Header ----------------------------------------------------------------*/
#include "SplashScreen.hpp"
#include "Input.hpp"
#include "Sprite.hpp"
#include "Application.hpp"

void SplashScreen::Initialize()
{
	logo = new Object();
	logo->SetTranslation({ 0,0 });
	logo->SetScale({ 500, 150 });
	logo->SetMesh(mesh::CreateBox());
	logo->AddComponent(new Sprite("asset/images/Splash/DigiPen_.png"));

	Objectmanager_.AddObject(logo);
}

void SplashScreen::Update(float dt)
{
	time_count += dt;

	if(ischange)
	{
		if (time_count < 4.0f)
		{
			logo->SetScale({ logo->GetTransform().GetScale().x + 220 * dt,
			 logo->GetTransform().GetScale().y + 55 * dt });
		}
		else if(time_count > 4.0f)
			StateManager_.BackToMainMenu();
	}
	else
	{
		if (logo->GetTransform().GetScale().x < 1300.0f &&
			logo->GetTransform().GetScale().y < 700.0f)
		{
			logo->SetScale({ logo->GetTransform().GetScale().x + 220 * dt,
			 logo->GetTransform().GetScale().y + 55 * dt });
		}
		else
		{
			time_count = 0;
			ischange = true;
			logo->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/Splash/fmod.png");
			logo->SetScale({ 300, 150 });
		}
	}

	if (Input::IsKeyTriggered(GLFW_KEY_SPACE))
		StateManager_.BackToMainMenu();
}


void SplashScreen::ShutDown()
{
	UnLoad();
}
