#include "Credit.hpp"
#include "Objectmanager.hpp"

void Credit::Initialize()
{
	AudioManager_.LoadSong("asset/sounds/Credit.mp3");
	AudioManager_.PlaySong("asset/sounds/Credit.mp3");

	Object* background = new Object();
	background->SetTranslation({ 0, 0 });
	background->SetDepth(0.98f);
	background->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width + 100), static_cast<float>(Application_.GetGLFWvidmode()->height + 100) });
	background->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	background->SetObjectType(ObjectType::Button);
	background->AddComponent(new Animation("asset/images/Page/BackgroundDay.png", "day", 16, 0.15f, true));

	m_credit1 = new Object();
	m_credit1->SetTranslation({ 0, 0 });
	m_credit1->SetScale(screen_size);
	m_credit1->SetDepth(BACKGROUND);
	m_credit1->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	m_credit1->SetObjectType(ObjectType::Background);
	m_credit1->AddComponent(new Sprite("asset/images/Page/CreditPage1.png"));

	m_credit2 = new Object();
	m_credit2->SetTranslation({ 0, 0 });
	m_credit2->SetScale(screen_size);
	m_credit2->SetDepth(BACKGROUND);
	m_credit2->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	m_credit2->SetObjectType(ObjectType::Background);
	m_credit2->AddComponent(new Sprite("asset/images/Page/CreditPage2.png"));
	m_credit2->GetMesh().Invisible();

	m_credit3 = new Object();
	m_credit3->SetTranslation({ 0, 0 });
	m_credit3->SetScale(screen_size);
	m_credit3->SetDepth(BACKGROUND);
	m_credit3->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	m_credit3->SetObjectType(ObjectType::Background);
	m_credit3->AddComponent(new Sprite("asset/images/Page/CreditPage3.png"));
	m_credit3->GetMesh().Invisible();

	Objectmanager_.AddObject(m_credit1);
	Objectmanager_.AddObject(m_credit2);
	Objectmanager_.AddObject(m_credit3);
	Objectmanager_.AddObject(background);
}

void Credit::Update(float dt)
{
	timer += dt;

	if(!page2 && !page3)
	{
		if(timer > 5.f)
		{
			page2 = true;
			page1 = false;
		}
	}
	else
	{
		if(timer > 10.f)
		{
			page2 = false;
			page3 = true;
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
		if(timer > 15.f)
			StateManager_.BackToMainMenu();
	}
	else
	{
		m_credit3->GetMesh().Invisible();
	}
}

void Credit::ShutDown()
{
	UnLoad();
}
