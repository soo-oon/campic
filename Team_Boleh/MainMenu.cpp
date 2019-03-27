#include "MainMenu.hpp"
#include "Capture.hpp"
#include "UI.hpp"
#include "Engine.hpp"

void MainMenu::Initialize()
{
	player_camera = new Object();
	player_camera->SetScale({ 300.0f, 175.0f });
	player_camera->SetTranslation(Input::GetMousePos());
	player_camera->SetDepth(-0.2f);
	player_camera->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	player_camera->SetObjectType(ObjectType::None);
	player_camera->AddComponent(new Animation("asset/images/camera_frame.png", "basic_camera", 2, 0.5, true));
	player_camera->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/cheese.png", "cheese", 2, 0.5, true);
	container.push_back(player_camera);

	start_button = new Object();
	start_button->SetScale({ 200.f, 70.f });
	start_button->SetTranslation({ -300,0 });
	start_button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	start_button->SetObjectType(ObjectType::None);
	start_button->AddComponent(new Sprite("asset/images/UI/StartButton.png"));
	start_button->AddComponent(new UI("Start"));
	container.push_back(start_button);

	option_button = new Object();
	option_button->SetScale({ 200.f, 70.f });
	option_button->SetTranslation({ 0,0 });
	option_button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	option_button->SetObjectType(ObjectType::None);
	option_button->AddComponent(new Sprite("asset/images/UI/OptionButton.png"));
	option_button->AddComponent(new UI("Option"));
	container.push_back(option_button);

	quit_button = new Object();
	quit_button->SetScale({ 200.f, 70.f });
	quit_button->SetTranslation({ 300,0 });
	quit_button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	quit_button->SetObjectType(ObjectType::None);
	quit_button->AddComponent(new Sprite("asset/images/UI/QuitButton.png"));
	quit_button->AddComponent(new UI("Quit"));
	container.push_back(quit_button);

	for(auto& i : container)
	{
		Objectmanager_.AddObject(i);
	}
}

void MainMenu::Update(float dt)
{
	player_camera->SetTranslation(Input::GetMousePos());

	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		click = true;
		player_camera->GetComponentByTemplate<Animation>()->ChangeAnimation("cheese");

		if (click)
		{
			player_camera->GetMesh().Decrease_Alpha(5);
			if (player_camera->GetMesh().GetColor(0).Alpha <= 15)
			{
				player_camera->GetComponentByTemplate<Animation>()->ChangeAnimation("basic_camera");
				player_camera->GetMesh().ChangeColor({ 255,255,255,255 });
				click = false;
			}
		}
	}
}


void MainMenu::ShutDown()
{
	UnLoad();
}
