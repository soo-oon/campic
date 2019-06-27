/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : MainMenu.cpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : TaeWook Kang
Secondary :
- End Header ----------------------------------------------------------------*/
#include "MainMenu.hpp"
#include "UI.hpp"
#include "Engine.hpp"
#include "DepthValue.hpp"
#include <iostream>
#include "HUD_Level.hpp"
#include "Button.hpp"

void MainMenu::Initialize()
{
	AudioManager_.PlaySong("asset/sounds/MainMenu_BGM.mp3");


	Object* camera = new Object();
	camera->SetTranslation({ -100, 0 });
	camera->SetScale({ 1280,800 });
	camera->SetDepth(BACKGROUND + 0.01f);
	camera->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	camera->SetObjectType(ObjectType::Button);
	camera->AddComponent(new Sprite("asset/images/Page/TitlePage.png"));

	Object* background = new Object();
	background->SetTranslation({ 0, 0 });
	background->SetDepth(0.98f);
	background->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width + 100), static_cast<float>(Application_.GetGLFWvidmode()->height + 100) });
	background->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	background->SetObjectType(ObjectType::Button);
	background->AddComponent(new Animation("asset/images/Page/BackgroundDay.png", "day", 16, 0.15f, true));

	Object* Start = new Object();
	Start->SetTranslation({600, 400});
	Start->SetScale({ 300,150 });
	Start->SetDepth(HUD_OBJECT);
	Start->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Start->SetObjectType(ObjectType::Button);
	Start->AddComponent(new UI("LevelSelector"));
	Start->AddComponent(new Sprite("asset/images/UI/StartButton.png"));
	
	Object* Option = new Object();
	Option->SetTranslation({ 600, 200 });
	Option->SetScale({ 300,150 });
	Option->SetDepth(HUD_OBJECT);
	Option->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Option->SetObjectType(ObjectType::Button);
	Option->AddComponent(new UI("Option"));
	Option->AddComponent(new Sprite("asset/images/UI/OptionButton.png"));

	Object* HowToPlay = new Object();
	HowToPlay->SetTranslation({ 600, 0 });
	HowToPlay->SetScale({ 300,150 });
	HowToPlay->SetDepth(HUD_OBJECT);
	HowToPlay->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	HowToPlay->SetObjectType(ObjectType::Button);
	HowToPlay->AddComponent(new UI("HowToPlay"));
	HowToPlay->AddComponent(new Sprite("asset/images/UI/HowToPlayButton.png"));

	Object* Credit = new Object();
	Credit->SetTranslation({ 600, -200 });
	Credit->SetScale({ 300,150 });
	Credit->SetDepth(HUD_OBJECT);
	Credit->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Credit->SetObjectType(ObjectType::Button);
	Credit->AddComponent(new UI("Credit"));
	Credit->AddComponent(new Sprite("asset/images/UI/CreditButton.png"));

	Object* Quit = new Object();
	Quit->SetTranslation({ 600, -400 });
	Quit->SetScale({ 300,150 });
	Quit->SetDepth(HUD_OBJECT);
	Quit->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Quit->SetObjectType(ObjectType::Button);
	Quit->AddComponent(new UI("Quit"));
	Quit->AddComponent(new Sprite("asset/images/UI/QuitButton.png"));


        are_you_sure = new Object();
        are_you_sure->SetTranslation({ 0,34 });
        are_you_sure->SetScale({ 384,192 });
        are_you_sure->SetDepth(-0.93f);
        are_you_sure->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
        are_you_sure->SetObjectType(ObjectType::None);
        are_you_sure->AddComponent(new Sprite("asset/images/UI/AreYouSure.png"));
        are_you_sure->GetMesh().Invisible();

        m_yes = new Object();
        m_yes->SetTranslation({ -70,2 });
        m_yes->SetScale({ 64,64 });
        m_yes->SetDepth(-0.95f);
        m_yes->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
        m_yes->SetObjectType(ObjectType::None);
        m_yes->AddComponent(new Sprite("asset/images/UI/Yes.png"));
        m_yes->GetMesh().Invisible();
        m_yes->AddInitComponent(new UI("yes."));

        m_no = new Object();
        m_no->SetTranslation({ 70,2 });
        m_no->SetScale({ 64,64 });
        m_no->SetDepth(-0.95f);
        m_no->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
        m_no->SetObjectType(ObjectType::None);
        m_no->AddComponent(new Sprite("asset/images/UI/No.png"));
        m_no->GetMesh().Invisible();
        m_no->AddInitComponent(new UI("no."));


	button_.AddObject(Start);
	button_.AddObject(Option);
	button_.AddObject(Credit);
	button_.AddObject(Quit);
	button_.AddObject(HowToPlay);
	button_.AddObject(m_yes);
	button_.AddObject(m_no);
	Objectmanager_.AddObject(are_you_sure);
	Objectmanager_.AddObject(background);
	Objectmanager_.AddObject(camera);
}

void MainMenu::Quitstate()
{
    if (!are_you_sure->Isvisible()) {
        are_you_sure->SetVisible();
        m_yes->SetVisible();
        m_no->SetVisible();
    }
    if(button_.IntersectionCheck(Input::GetMousePos()))
    {
        std::string temp = button_.GetSelect().first->GetComponentByTemplate<UI>()->GetId();



        if (temp == "yes.")
        {
            button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
            button_.GetSelect().second = CollisionState::WasCollided;
        }

        if (temp == "no.")
        {
            button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
            button_.GetSelect().second = CollisionState::WasCollided;
        }

        if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
        {
            if (temp == "yes.")
                Engine::IsQuit = true;
            else if (temp == "no.")
            {
                are_you_sure->SetInvisible();
                m_yes->SetInvisible();
                m_no->SetInvisible();
                callQuit = false;
            }
        }
    }

    if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
    {
        are_you_sure->SetInvisible();
        m_yes->SetInvisible();
        m_no->SetInvisible();
        callQuit = false;
    }
}

void MainMenu::Update(float dt)
{
    if(callQuit)
        Quitstate();
	if (button_.IntersectionCheck(Input::GetMousePos()))
	{
            std::string temp = button_.GetSelect().first->GetComponentByTemplate<UI>()->GetId();

            if (temp == "LevelSelector")
            {
                button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
                button_.GetSelect().second = CollisionState::WasCollided;
            }
            else if (temp == "Quit")
            {
                button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
                button_.GetSelect().second = CollisionState::WasCollided;
            }
            else if (temp == "Credit")
            {
                button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
                button_.GetSelect().second = CollisionState::WasCollided;
            }
            else if (temp == "HowToPlay")
            {
                button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
                button_.GetSelect().second = CollisionState::WasCollided;
            }
			else if(temp == "Option")
			{
				button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
				button_.GetSelect().second = CollisionState::WasCollided;
			}
			


		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{

			if (temp == "LevelSelector")
			{
 				AudioManager_.PlaySFX("asset/sounds/Button.wav",0.1f);
				BackToMenu();
			}

			else if (temp == "Option")
			{
				AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.1f);
				HUD_Level::IsOptionWindowOpen = !HUD_Level::IsOptionWindowOpen;
				StateManager_.TogglePause();
			}

			else if (temp == "Quit")
			{
				AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.1f);
                                button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
                                callQuit = true;
			}

			else if (temp == "Credit")
			{
				AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.1f);
                                button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
				StateManager_.ToCredit();
			}

			else if (temp == "HowToPlay")
			{
				AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.1f);
                                button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
				StateManager_.ToHowToPlay();
			}
		}
	}
        else
        {
            for (auto&i : button_.GetContainer())
            {
                i.get()->GetMesh().ChangeColor({255, 255, 255});
            }
        }
}


void MainMenu::ShutDown()
{
	UnLoad();
}
