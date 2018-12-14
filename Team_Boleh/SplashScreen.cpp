/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  SplashScreen.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#include "SplashScreen.hpp"
#include <iostream>
#include "Input.hpp"
#include "Sprite.hpp"

void SplashScreen::Initialize()
{
	GetObjectManager()->AddObject("Digipen_Logo");
	GetObjectManager()->AddObject("BackGround");

	logo = GetObjectManager()->FindObject("Digipen_Logo").get();
	logo->SetTranslation({ 0,0 });
	logo->SetScale({ 300, 150 });
	logo->SetMesh(mesh::CreateBox());
	logo->AddComponent(new Sprite());
	logo->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/DigiPen_.png");

	background = GetObjectManager()->FindObject("BackGround").get();
	background->SetTranslation({ 0,0 });
	background->SetMesh(mesh::CreateBox());
	background->SetDepth(0.9f);
	background->AddComponent(new Sprite());
	background->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/UI/Menu_background.png");
}

void SplashScreen::Update(float dt)
{
	background->SetScale(GetStateScreenSize());

	time_count += dt;

	if(ischange)
	{
		if (time_count < 2.0f)
		{
			logo->SetScale({ logo->GetTransform().GetScale().x + 220 * dt,
			 logo->GetTransform().GetScale().y + 55 * dt });
		}
		else if(time_count > 3.0f)
			ChangeLevel("StartMenu");
	}
	else
	{

		if (logo->GetTransform().GetScale().x < 920.0f &&
			logo->GetTransform().GetScale().y < 420.0f)
		{
			logo->SetScale({ logo->GetTransform().GetScale().x + 220 * dt,
			 logo->GetTransform().GetScale().y + 55 * dt });
		}
		else
		{
			time_count = 0;
			ischange = true;
			logo->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/fmod.png");
			logo->SetScale({ 300, 150 });
		}
	}

	if(Input::IsKeyTriggered(GLFW_KEY_SPACE))
		ChangeLevel("StartMenu");
}


void SplashScreen::ShutDown()
{
}
