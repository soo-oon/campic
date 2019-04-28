#include "MainMenu.hpp"
#include "UI.hpp"
#include "Engine.hpp"

void MainMenu::Initialize()
{
	Object* background = new Object();
	background->SetTranslation({ 0, 0 });
	background->SetScale({ 1000,940 });
	background->SetDepth(0.2f);
	background->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	background->SetObjectType(ObjectType::Button);
	background->AddComponent(new Sprite("asset/images/UI/MainPage.png"));

	Objectmanager_.AddObject(background);

	Object* Start = new Object();
	Start->SetTranslation({-120, -100});
	Start->SetScale({ 150,100 });
	Start->SetDepth(-0.1f);
	Start->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Start->SetObjectType(ObjectType::Button);
	Start->AddComponent(new UI("LevelSelector"));
	Start->AddComponent(new Sprite("asset/images/UI/StartButton.png"));

	Objectmanager_.AddObject(Start);

	Object* Option = new Object();
	Option->SetTranslation({ 150, -100 });
	Option->SetScale({ 170,170 });
	Option->SetDepth(-0.1f);
	Option->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Option->SetObjectType(ObjectType::Button);
	//Option->AddComponent(new UI("LevelSelector"));
	Option->AddComponent(new Sprite("asset/images/UI/OptionButton.png"));

	Objectmanager_.AddObject(Option);

	Object* Credit = new Object();
	Credit->SetTranslation({ -120, -350 });
	Credit->SetScale({ 150,150 });
	Credit->SetDepth(-0.1f);
	Credit->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Credit->SetObjectType(ObjectType::Button);
	//Credit->AddComponent(new UI("LevelSelector"));
	Credit->AddComponent(new Sprite("asset/images/UI/CreditButton.png"));

	Objectmanager_.AddObject(Credit);

	Object* Quit = new Object();
	Quit->SetTranslation({ 120, -350 });
	Quit->SetScale({ 150,100 });
	Quit->SetDepth(-0.1f);
	Quit->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Quit->SetObjectType(ObjectType::Button);
	Quit->AddComponent(new UI("Quit"));
	Quit->AddComponent(new Sprite("asset/images/UI/QuitButton.png"));

	Objectmanager_.AddObject(Quit);
}

void MainMenu::Update(float dt)
{
	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		m_Select = Input::ClickHudObject(-0.1f);

		if (m_Select)
		{
			if (m_Select->GetComponentByTemplate<UI>()->GetId() == "LevelSelector")
				BackToMenu();

			if (m_Select->GetComponentByTemplate<UI>()->GetId() == "Quit")
				Engine::IsQuit = true;
		}
	}
}


void MainMenu::ShutDown()
{
	UnLoad();
}
