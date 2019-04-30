#include "HUD_Level.hpp"
#include "HUD.hpp"
#include "Capture.hpp"
#include "UI.hpp"
#include "ObjectDepth.hpp"

void HUD_Level::Initialize()
{
	Object* h_capture_limit = new Object();


	h_option_window = new Object();
	h_option_window->SetScale({ screen_size.x-200, screen_size.y-200 });
	h_option_window->SetDepth(-0.6f);
	h_option_window->SetMesh(mesh::CreateBox(1, { 0,0,0,255 }));
	h_option_window->SetObjectType(ObjectType::None);
	h_option_window->GetMesh().Invisible();

	h_cheese = new Object();
	h_cheese->SetScale(Application_.GetScreenSize());
	h_cheese->SetDepth(-0.5f);
	h_cheese->SetMesh(mesh::CreateBox(1, Colors::Yellow));
	h_cheese->SetObjectType(ObjectType::Background);
	h_cheese->SetInvisible();
	h_cheese->GetMesh().Invisible();

	h_fullscreen_button = new Object();
	h_fullscreen_button->SetTranslation(vector2(screen_size.x-1200, screen_size.y-1000));
	h_fullscreen_button->SetScale(screen_size/10);
	h_fullscreen_button->SetDepth(HUD_BUTTON);
	h_fullscreen_button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	h_fullscreen_button->SetObjectType(ObjectType::HUD_Button);
	h_fullscreen_button->AddComponent(new Sprite("asset/images/UI/EmptyBox.png"));
	h_fullscreen_button->AddComponent(new UI("fullscreen"));
	h_fullscreen_button->GetMesh().Invisible();

	HUD_.Add_HUD_Object(h_fullscreen_button);
	HUD_.Add_HUD_Object(h_cheese);
	HUD_.Add_HUD_Object(h_option_window);

	HUD_.Toggle_HUD_Active();
}

void HUD_Level::Update(float dt)
{
	if (auto player = StateManager_.GetCurrentState()->GetPlayerObjectPointer();
		player != nullptr)
	{
		h_cheese->SetTranslation(player->GetTransform().GetTranslation());
	}
	if(StateManager_.GetCurrentState()->GetCaptureObjectPointer() != nullptr)
	{
		if(auto cheese = StateManager_.GetCurrentState()->GetCaptureObjectPointer()->GetComponentByTemplate<Capture>();
			cheese != nullptr)
		{
			if (cheese->IsCheese())
			{
				if (!h_cheese->Isvisible())
					h_cheese->SetVisible();

				h_cheese->GetMesh().Decrease_Alpha(10);

				if (h_cheese->GetMesh().GetColor(0).Alpha <= 15)
				{
					h_cheese->GetMesh().SetAlphaFill();
					h_cheese->SetInvisible();
					StateManager_.GetCurrentState()->GetCaptureObjectPointer()->GetComponentByTemplate<Capture>()->SetCheese(false);
				}
			}
			else
			{
				if (h_cheese->Isvisible())
				{
					h_cheese->SetInvisible();
					h_cheese->GetMesh().SetAlphaZero();
				}
			}
		}
	}

	if (StateManager_.GetCurrentState()->GetCurrentStateInfo() == State_Information::Game)
	{
		if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
		{
			IsOptionWindowOpen = !IsOptionWindowOpen;
			if (h_option_window->GetMesh().IsVisible())
			{
				h_option_window->GetMesh().Invisible();
				h_fullscreen_button->GetMesh().Invisible();
			}
			else
			{
				h_option_window->GetMesh().Visible();
				h_fullscreen_button->GetMesh().Visible();
				StateManager_.Pause();
			}
		}

		if (IsOptionWindowOpen)
		{
			if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
			{
				h_select = Input::ClickHUDButton();

				if (h_select->GetComponentByTemplate<UI>() != nullptr &&
					h_select->GetComponentByTemplate<UI>()->GetId() == "fullscreen")
				{
					Application_.FullScreen();
				}
			}
		}
	}
}

void HUD_Level::ShutDown()
{
}

void HUD_Level::CreateHudButton(vector2 pos, vector2 scale, std::string id)
{
	Object* button = new Object();

	button->SetTranslation(pos);
	button->SetScale(scale);
	button->SetDepth(-0.65f);
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::HUD_Button);
	button->AddComponent(new Sprite("asset/images/UI/EmptyBox.png"));
	button->AddComponent(new UI(id));

	HUD_.Add_HUD_Object(button);
}
