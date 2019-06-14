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
	background->AddComponent(new Animation("asset/images/Page/BackgroundNight.png", "Night", 16, 0.15f, true));

	Object* Start = new Object();
	Start->SetTranslation({600, 200});
	Start->SetScale({ 300,150 });
	Start->SetDepth(HUD_OBJECT);
	Start->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	Start->SetObjectType(ObjectType::Button);
	Start->AddComponent(new UI("LevelSelector"));
	Start->AddComponent(new Sprite("asset/images/UI/StartButton.png"));
	
	//Object* Option = new Object();
	//Option->SetTranslation({ 600, 200 });
	//Option->SetScale({ 300,150 });
	//Option->SetDepth(HUD_OBJECT);
	//Option->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	//Option->SetObjectType(ObjectType::Button);
	//Option->AddComponent(new UI("Option"));
	//Option->AddComponent(new Sprite("asset/images/UI/OptionButton.png"));

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

	//Objectmanager_.AddObject(mouse_icon);
	button_.AddObject(Start);
	//button_.AddObject(Option);
	button_.AddObject(Credit);
	button_.AddObject(Quit);
	Objectmanager_.AddObject(background);
	button_.AddObject(HowToPlay);
	Objectmanager_.AddObject(camera);
}

void MainMenu::Update(float dt)
{

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


		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			//std::string temp = button_.GetSelect().first->GetComponentByTemplate<UI>()->GetId();

			if (temp == "LevelSelector")
			{
 				AudioManager_.PlaySFX("asset/sounds/Button.wav",0.3f);
				BackToMenu();
				button_.RemoveContainer();
			}

			//else if (temp == "Option")
			//{
			//	AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.3f);
			//	HUD_Level::IsOptionWindowOpen = !HUD_Level::IsOptionWindowOpen;
			//	button_.RemoveContainer();
			//}

			else if (temp == "Quit")
			{
				AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.3f);
                                button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
				Engine::IsQuit = true;
				button_.RemoveContainer();
			}

			else if (temp == "Credit")
			{
				AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.3f);
                                button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
				StateManager_.ToCredit();
				button_.RemoveContainer();
			}

			else if (temp == "HowToPlay")
			{
				AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.3f);
                                button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
				StateManager_.ToHowToPlay();
				button_.RemoveContainer();
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
