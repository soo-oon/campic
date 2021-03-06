/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : HowToPlay.cpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : TaeWook Kang
Secondary :
- End Header ----------------------------------------------------------------*/
#include "HowToPlay.hpp"
#include "UI.hpp"
#include "Button.hpp"
#include "HUD_Level.hpp"

void HowToPlay::Initialize()
{
	mouse_icon = new Object();
	mouse_icon->SetTranslation({ 0,0 });
	mouse_icon->SetScale({ 50,50 });
	mouse_icon->SetDepth(-0.8f);
	mouse_icon->SetObjectType(ObjectType::None);
	mouse_icon->SetMesh(mesh::CreateBox());
	mouse_icon->AddComponent(new Sprite("asset/images/UI/MouseCursor.png"));

	Object* background = new Object();
	background->SetTranslation({ 0, 0 });
	background->SetDepth(0.98f);
	background->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width + 100), static_cast<float>(Application_.GetGLFWvidmode()->height + 100) });
	background->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	background->SetObjectType(ObjectType::Button);
	background->AddComponent(new Animation("asset/images/Page/BackgroundDay.png", "day", 16, 0.15f, true));

	Object* cam = new Object();
	cam->SetTranslation({ 0, 0 });
	cam->SetDepth(0.9f);
	cam->SetScale({ 1200,900 });
	cam->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	cam->SetObjectType(ObjectType::Button);
	cam->AddInitComponent(new Sprite("asset/images/Page/HowToPlay.png"));

	Objectmanager_.AddObject(background);

	button = new Object();
        button->SetTranslation({ 310.f, 290.f });
	button->SetScale({ 182,96 });
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::Button);
	button->AddInitComponent(new Sprite("asset/images/UI/Back.png"));

	Objectmanager_.AddObject(cam);
	Objectmanager_.AddObject(mouse_icon);
	button_.AddObject(button);
}

void HowToPlay::Update(float dt)
{
	mouse_icon->SetTranslation(Input::GetMousePos());

    if(Input::IsKeyAnyTriggered())
    {
        StateManager_.BackToMainMenu();
        if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
            HUD_Level::IsOptionWindowOpen = !HUD_Level::IsOptionWindowOpen;
    }

	if (button_.IntersectionCheck(Input::GetMousePos()))
	{
            button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.1f);
			StateManager_.BackToMainMenu();
		}
	}
        else
        {
            for (auto&i : button_.GetContainer())
            {
                i.get()->GetMesh().ChangeColor({ 255, 255, 255 });
            }
        }
        
}

void HowToPlay::ShutDown()
{
	UnLoad();
	m_select = nullptr;
	mouse_icon = nullptr;
	button = nullptr;
}
