#include "HUD_Level.hpp"
#include "HUD.hpp"
#include "Graphics.hpp"
#include "Capture.hpp"
#include "UI.hpp"

void HUD_Level::Initialize()
{
	vector2 screen_size = Application_.GetScreenSize();

	h_option_window = new Object();
	h_option_window->SetScale({ screen_size.x-300, screen_size.y-300 });
	h_option_window->SetDepth(-0.9f);
	h_option_window->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	h_option_window->SetObjectType(ObjectType::None);
	h_option_window->AddComponent(new Sprite("asset/images/Tiles/Non_Ani/Ground001.png"));
	h_option_window->GetMesh().Invisible();

	h_cheese = new Object();
	h_cheese->SetScale(Application_.GetScreenSize());
	h_cheese->SetDepth(-0.5f);
	h_cheese->SetMesh(mesh::CreateBox(1, Colors::Yellow));
	h_cheese->SetObjectType(ObjectType::Background);
	h_cheese->SetInvisible();
	h_cheese->GetMesh().Invisible();

	HUD_.Add_HUD_Object(h_cheese);
	//HUD_.Add_HUD_Object(h_option_window);

	HUD_.Toggle_HUD_Active();
}

void HUD_Level::Update(float dt)
{
	h_cheese->SetTranslation(StateManager_.GetCurrentState()->camera_center);

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

	if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
	{
		if (h_option_window->GetMesh().IsVisible())
			h_option_window->GetMesh().Invisible();
		else
			h_option_window->GetMesh().Visible();
	}
}

void HUD_Level::ShutDown()
{
}

void HUD_Level::CreateHudButton(vector2 pos, vector2 scale,/*,std::string & font*/std::string id)
{
	Object* button = new Object();

	button->SetTranslation(pos);
	button->SetScale(scale);
	button->SetDepth(-1.0f);
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::Button);
	button->AddComponent(new UI(id));

	Objectmanager_.AddObject(button);
}
