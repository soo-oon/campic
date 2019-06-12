#include "MainMenu.hpp"
#include "UI.hpp"
#include "Engine.hpp"
#include "DepthValue.hpp"
#include <iostream>
#include "HUD_Level.hpp"

void MainMenu::Initialize()
{
	AudioManager_.PlaySong("asset/sounds/MainMenu_BGM.mp3");

	//mouse_icon = new Object();
	//mouse_icon->SetTranslation({ 0,0 });
	//mouse_icon->SetScale({ 50,50 });
	//mouse_icon->SetDepth(depth::NearDepth);
	//mouse_icon->SetObjectType(ObjectType::None);
	//mouse_icon->SetMesh(mesh::CreateBox());
	//mouse_icon->AddComponent(new Sprite("asset/images/UI/MouseCursor.png"));

	Object* camera = new Object();
	camera->SetTranslation({ -100, 0 });
	camera->SetScale({ 1250,630 });
	camera->SetDepth(BACKGROUND+0.01f);
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
	Start->SetTranslation({450, 120});
	Start->SetScale({ 150,150 });
	Start->SetDepth(HUD_OBJECT);
	Start->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Start->SetObjectType(ObjectType::Button);
	Start->AddComponent(new UI("LevelSelector"));
	Start->AddComponent(new Sprite("asset/images/UI/StartButton.png"));
	
	Object* Option = new Object();
	Option->SetTranslation({ 650, 120 });
	Option->SetScale({ 150,150 });
	Option->SetDepth(HUD_OBJECT);
	Option->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Option->SetObjectType(ObjectType::Button);
	Option->AddComponent(new UI("Option"));
	Option->AddComponent(new Sprite("asset/images/UI/OptionButton.png"));

	Object* Credit = new Object();
	Credit->SetTranslation({ 450, -110 });
	Credit->SetScale({ 150,150 });
	Credit->SetDepth(HUD_OBJECT);
	Credit->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Credit->SetObjectType(ObjectType::Button);
	Credit->AddComponent(new UI("Credit"));
	Credit->AddComponent(new Sprite("asset/images/UI/CreditButton.png"));

	Object* Quit = new Object();
	Quit->SetTranslation({ 650, -110 });
	Quit->SetScale({ 150,150 });
	Quit->SetDepth(HUD_OBJECT);
	Quit->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Quit->SetObjectType(ObjectType::Button);
	Quit->AddComponent(new UI("Quit"));
	Quit->AddComponent(new Sprite("asset/images/UI/QuitButton.png"));

	//Objectmanager_.AddObject(mouse_icon);
	Objectmanager_.AddObject(Start);
	Objectmanager_.AddObject(Option);
	Objectmanager_.AddObject(Credit);
	Objectmanager_.AddObject(Quit);
	Objectmanager_.AddObject(background);
	Objectmanager_.AddObject(camera);
}

void MainMenu::Update(float dt)
{
	//mouse_icon->SetTranslation(Input::GetMousePos());

	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		m_Select = Input::ClickObject(ObjectDepth::HUD_OBJECT);

		if (m_Select)
		{
			if (m_Select->GetComponentByTemplate<UI>()->GetId() == "LevelSelector")
				BackToMenu();

			if (m_Select->GetComponentByTemplate<UI>()->GetId() == "Option")
				HUD_Level::IsOptionWindowOpen = !HUD_Level::IsOptionWindowOpen;

			if (m_Select->GetComponentByTemplate<UI>()->GetId() == "Quit")
				Engine::IsQuit = true;

			if (m_Select->GetComponentByTemplate<UI>()->GetId() == "Credit")
				StateManager_.ToCredit();
		}
	}
}


void MainMenu::ShutDown()
{
	UnLoad();
}
