#include "HowToPlay.hpp"
#include "UI.hpp"
#include "Button.hpp"

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
	background->AddComponent(new Animation("asset/images/Page/BackgroundNight.png", "Night", 16, 0.15f, true));

	Object* cam = new Object();
	cam->SetTranslation({ 0, 0 });
	cam->SetDepth(0.9f);
	cam->SetScale({ 1200,900 });
	cam->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	cam->SetObjectType(ObjectType::Button);
	cam->AddInitComponent(new Sprite("asset/images/Page/HowToPlay.png"));

	Objectmanager_.AddObject(background);

	button = new Object();
	button->SetTranslation({ 880, -500 });
	button->SetScale({ 182,96 });
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::Button);
	button->AddInitComponent(new Sprite("asset/images/UI/BackButton.png"));

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
    }

	if (button_.IntersectionCheck(Input::GetMousePos()))
	{
		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.3f);
			StateManager_.BackToMainMenu();
		}
	}
}

void HowToPlay::ShutDown()
{
	UnLoad();
}
