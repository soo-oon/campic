#include "HowToPlay.hpp"
#include "UI.hpp"

void HowToPlay::Initialize()
{
	Object* background = new Object();
	background->SetTranslation({ 0, 0 });
	background->SetDepth(0.98f);
	background->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width + 100), static_cast<float>(Application_.GetGLFWvidmode()->height + 100) });
	background->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	background->SetObjectType(ObjectType::Button);
	background->AddInitComponent(new Sprite("asset/images/Page/HowToPlay.png"));

	Objectmanager_.AddObject(background);

	Object* button = new Object();
	button->SetTranslation({ 400, -400 });
	button->SetDepth(HUD_BUTTON);
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::Button);
	button->AddInitComponent(new Sprite("asset/images/UI/BackButton.png"));
	button->AddInitComponent(new UI("back"));

	Objectmanager_.AddObject(button);
}

void HowToPlay::Update(float dt)
{
	if(Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		m_select = Input::ClickHUDButton();

		if(m_select)
		{
			if(m_select->GetComponentByTemplate<UI>()->GetId() == "Back")
			{
				StateManager_.BackToMainMenu();
				m_select = nullptr;
			}
		}
	}

    if(Input::IsKeyAnyTriggered())
    {
        StateManager_.BackToMainMenu();
    }
}

void HowToPlay::ShutDown()
{
	UnLoad();
}
