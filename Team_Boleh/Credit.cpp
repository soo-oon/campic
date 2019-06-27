/* Start Header ---------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Credit.cpp
Language  : C++
Platform  : Visual Studio 2017
Project   : CamPic
Primary   : TaeWook Kang
Secondary :
- End Header ----------------------------------------------------------------*/
#include "Credit.hpp"
#include "Objectmanager.hpp"
#include "Button.hpp"

void Credit::Initialize()
{
    timer = 0.f;
    page1 = true;
    page2 = false;
    page3 = false;

	AudioManager_.LoadSong("asset/sounds/Credit.mp3");
	AudioManager_.PlaySong("asset/sounds/Credit.mp3");

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

	m_credit1 = new Object();
	m_credit1->SetTranslation({ 0, 0 });
	m_credit1->SetScale({ 1200,900 });
	m_credit1->SetDepth(BACKGROUND);
	m_credit1->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	m_credit1->SetObjectType(ObjectType::Background);
	m_credit1->AddComponent(new Sprite("asset/images/Page/CreditPage1.png"));

	m_credit2 = new Object();
	m_credit2->SetTranslation({ 0, 0 });
	m_credit2->SetScale({ 1200,900 });
	m_credit2->SetDepth(BACKGROUND);
	m_credit2->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	m_credit2->SetObjectType(ObjectType::Background);
	m_credit2->AddComponent(new Sprite("asset/images/Page/CreditPage2.png"));
	m_credit2->GetMesh().Invisible();

	m_credit3 = new Object();
	m_credit3->SetTranslation({ 0, 0 });
	m_credit3->SetScale({ 1200,900 });
	m_credit3->SetDepth(BACKGROUND);
	m_credit3->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	m_credit3->SetObjectType(ObjectType::Background);
	m_credit3->AddComponent(new Sprite("asset/images/Page/CreditPage3.png"));
	m_credit3->GetMesh().Invisible();

	m_credit4 = new Object();
        m_credit4->SetTranslation({ 0, 0 });
        m_credit4->SetScale({ 1200,900 });
        m_credit4->SetDepth(BACKGROUND);
        m_credit4->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
        m_credit4->SetObjectType(ObjectType::Background);
        m_credit4->AddComponent(new Sprite("asset/images/Page/CreditPage4.png"));
        m_credit4->GetMesh().Invisible();
	m_credit5 = new Object();
        m_credit5->SetTranslation({ 0, 0 });
        m_credit5->SetScale({ 1200,900 });
        m_credit5->SetDepth(BACKGROUND);
        m_credit5->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
        m_credit5->SetObjectType(ObjectType::Background);
        m_credit5->AddComponent(new Sprite("asset/images/Page/CreditPage5.png"));
        m_credit5->GetMesh().Invisible();
	m_credit6 = new Object();
        m_credit6->SetTranslation({ 0, 0 });
        m_credit6->SetScale({ 1200,900 });
        m_credit6->SetDepth(BACKGROUND);
        m_credit6->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
        m_credit6->SetObjectType(ObjectType::Background);
        m_credit6->AddComponent(new Sprite("asset/images/Page/CreditPage6.png"));
        m_credit6->GetMesh().Invisible();

	button = new Object();
	button->SetTranslation({ 310.f, 280.f});
	button->SetScale({ 182,96 });
	button->SetDepth(-0.5f);
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::Button);
	button->AddInitComponent(new Sprite("asset/images/UI/Back.png"));

	Objectmanager_.AddObject(m_credit1);
	Objectmanager_.AddObject(m_credit2);
	Objectmanager_.AddObject(m_credit3);
	Objectmanager_.AddObject(m_credit4);
	Objectmanager_.AddObject(m_credit5);
	Objectmanager_.AddObject(m_credit6);
	Objectmanager_.AddObject(mouse_icon);
	Objectmanager_.AddObject(background);

	button_.AddObject(button);
}

void Credit::Update(float dt)
{
	mouse_icon->SetTranslation(Input::GetMousePos());

	timer += dt;

	if(!page2 && !page3 && !page4 && !page5 && !page6)
	{
		if(timer > 2.f)
		{
			page2 = true;
			page1 = false;
		}
	}
	else
	{
		if(timer > 4.f&& timer < 6.f)
		{
			page2 = false;
			page3 = true;
		}
            else if(timer > 6.f && timer < 8.f)
            {
                page3 = false;
                page4 = true;
            }
            else if(timer > 8.f&& timer < 10.f)
            {
                page4 = false;
                page5 = true;
            }
            else if(timer > 10.f&& timer < 12.f)
            {
                page5 = false;
                page6 = true;
            }
	}

	if(page1)
	{
		m_credit1->GetMesh().Visible();
	}
	else
	{
		m_credit1->GetMesh().Invisible();
	}

	if (page2)
	{
		m_credit2->GetMesh().Visible();
	}
	else
	{
		m_credit2->GetMesh().Invisible();
	}

	if(page3)
	{
		m_credit3->GetMesh().Visible();
	}
        else
        {
            m_credit3->GetMesh().Invisible();
        }
	if(page4)
	{
		m_credit4->GetMesh().Visible();
	}
        else
        {
            m_credit4->GetMesh().Invisible();
        }
	if(page5)
	{
		m_credit5->GetMesh().Visible();
	}
        else
        {
            m_credit5->GetMesh().Invisible();
        }
	if(page6)
	{
		m_credit6->GetMesh().Visible();
                if (timer > 14.f)
                {
                    page1 = true;
                    page2 = false;
                    page3 = false;
                    page4 = false;
                    page5 = false;
                    page6 = false;
                    StateManager_.BackToMainMenu();
                }
	}
	else
	{
		m_credit6->GetMesh().Invisible();
	}

    if (Input::IsKeyAnyTriggered())
    {
        StateManager_.BackToMainMenu();
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

void Credit::ShutDown()
{
	UnLoad();
	m_credit1 = nullptr;
	m_credit2 = nullptr;
	m_credit3 = nullptr;
	m_credit4 = nullptr;
	mouse_icon = nullptr;
	button = nullptr;
}
