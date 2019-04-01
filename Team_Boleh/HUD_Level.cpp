#include "HUD_Level.hpp"
#include "HUD.hpp"
#include <iostream>
#include "Graphics.hpp"
#include "Player.hpp"
#include "Capture.hpp"

void HUD_Level::Initialize()
{
	g_Option = new Object();
	g_Option->SetScale({ 500, 500 });
	g_Option->SetDepth(-0.5f);
	g_Option->SetMesh(mesh::CreateBox(1, { 255,0,0,255 }));
	g_Option->SetObjectType(ObjectType::None);
	g_Option->GetMesh().Invisible();

	h_cheese = new Object();
	h_cheese->SetScale(Application_.GetScreenSize());
	h_cheese->SetDepth(-0.5f);
	h_cheese->SetMesh(mesh::CreateBox(1, Colors::Yellow));
	h_cheese->SetObjectType(ObjectType::Background);
	h_cheese->SetInvisible();
	h_cheese->GetMesh().Invisible();

	HUD_.Add_HUD_Object(h_cheese);

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
		if (g_Option->GetMesh().IsVisible())
			g_Option->GetMesh().Invisible();
		else
			g_Option->GetMesh().Visible();
	}
}

void HUD_Level::ShutDown()
{
}
