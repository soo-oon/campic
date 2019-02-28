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
#include "Graphics.hpp"
#include "Application.hpp"

void SplashScreen::Initialize()
{
	logo.SetTranslation({ 0,0 });
	logo.SetScale({ 500, 150 });
	logo.SetMesh(mesh::CreateBox());
	logo.AddComponent(new Sprite("asset/images/DigiPen_.png"));
	//logo.GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/DigiPen_.png");

	int w, h;
	glfwGetWindowSize(Application_.GetWindow(), &w, &h);

	background.SetTranslation({ 0,0 });
    background.SetScale(vector2(static_cast<float>(w), static_cast<float>(h)));
	background.SetMesh(mesh::CreateBox());
	background.SetDepth(0.9f);
	background.AddComponent(new Sprite("asset/images/UI/Menu_background.png"));
	//background.GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/UI/Menu_background.png");

	Objectmanager_.AddObject(logo);
	Objectmanager_.AddObject(background);
}

void SplashScreen::Update(float dt)
{
	time_count += dt;

	if(ischange)
	{
		if (time_count < 2.0f)
		{
			logo.SetScale({ logo.GetTransform().GetScale().x + 220 * dt,
			 logo.GetTransform().GetScale().y + 55 * dt });
		}
		else if(time_count > 3.0f)
			ChangeLevel("remake");
	}
	else
	{

		if (logo.GetTransform().GetScale().x < 920.0f &&
			logo.GetTransform().GetScale().y < 420.0f)
		{
			logo.SetScale({ logo.GetTransform().GetScale().x + 220 * dt,
			 logo.GetTransform().GetScale().y + 55 * dt });
		}
		else
		{
			time_count = 0;
			ischange = true;
			logo.GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/fmod.png");
			logo.SetScale({ 300, 150 });
		}
	}

	if(Input::IsKeyTriggered(GLFW_KEY_SPACE))
		ChangeLevel("remake");
}


void SplashScreen::ShutDown()
{
}
