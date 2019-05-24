#include "HUD_Level.hpp"
#include "HUD.hpp"
#include "Capture.hpp"
#include "UI.hpp"
#include "ObjectDepth.hpp"
#include <iostream>

void HUD_Level::Initialize()
{
	h_capture_limit = new Object();
	h_capture_limit->SetTranslation(vector2(screen_size.x/2 -200, screen_size.y / 2 - 100));
	h_capture_limit->SetScale(vector2{ screen_size.x / 10, screen_size.y/10 });
	h_capture_limit->SetDepth(-0.5f);
	h_capture_limit->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	h_capture_limit->SetObjectType(ObjectType::None);
	h_capture_limit->AddInitComponent(new Sprite("asset/images/UI/CaptureLimit.png"));
	h_capture_limit->SetInvisible();
	h_capture_limit->GetMesh().Invisible();
	container.push_back(h_capture_limit);

	h_capture_number = new Object();
	h_capture_number->SetTranslation(vector2(screen_size.x/2 -130 , 340));
	h_capture_number->SetScale({ 2.8 });
	h_capture_number->SetDepth(-0.6f);
	h_capture_number->AddComponent(new Font(L"asset/font/sansation.fnt", L"0"));
	h_capture_number->GetComponentByTemplate<Font>()->SetFillColor(Colors::Black);
	h_capture_number->SetInvisible();
	h_capture_number->GetMesh().Invisible();
	container.push_back(h_capture_number);

	h_cheese = new Object();
	h_cheese->SetScale(Application_.GetScreenSize());
	h_cheese->SetDepth(-0.5f);
	h_cheese->SetMesh(mesh::CreateBox(1, Colors::Yellow));
	h_cheese->SetObjectType(ObjectType::Background);
	h_cheese->SetInvisible();
	h_cheese->GetMesh().Invisible();
	container.push_back(h_cheese);

	////////////OPTION WINDOW
	h_option_window = new Object();
	h_option_window->SetScale({ screen_size.x - 200, screen_size.y - 200 });
	h_option_window->SetDepth(-0.6f);
	h_option_window->SetMesh(mesh::CreateBox(1, { 0,0,0,255 }));
	h_option_window->SetObjectType(ObjectType::None);
	h_option_window->GetMesh().Invisible();

	h_fullscreen_button = CreateHudButton(vector2(screen_size.x - 1000, screen_size.y - 1000), screen_size / 10,
		HUD_BUTTON, "asset/images/UI/EmptyBox.png", "fullscreen");

	h_bgm_scroll_bar = CreateHudButton(vector2(screen_size.x - 1000, screen_size.y - 800), screen_size / 3,
		-0.62f,"asset/images/UI/Icon_AdjustBar.png");

	h_bgm_scroll_button = CreateHudButton(vector2(screen_size.x - 1000, screen_size.y - 800), screen_size / 25,
		HUD_BUTTON,"asset/images/UI/Icon_AdjustBall.png", "scrollbutton");

	h_sfx_scroll_bar = CreateHudButton(vector2(screen_size.x - 1000, screen_size.y - 700), screen_size / 3,
		-0.62f,"asset/images/UI/Icon_AdjustBar.png");

	h_sfx_scroll_button = CreateHudButton(vector2(screen_size.x - 1000, screen_size.y - 700), screen_size / 25,
		HUD_BUTTON, "asset/images/UI/Icon_AdjustBall.png", "scrollbutton");

	h_mute_button = CreateHudButton(vector2(screen_size.x - 1000, screen_size.y - 900), screen_size / 10,
		HUD_BUTTON,"asset/images/UI/EmptyBox.png", "Mute");

	container.push_back(h_option_window);
	container.push_back(h_fullscreen_button);
	container.push_back(h_bgm_scroll_button);
	container.push_back(h_bgm_scroll_bar);
	container.push_back(h_sfx_scroll_button);
	container.push_back(h_sfx_scroll_bar);
	container.push_back(h_mute_button);

	for(auto& i : container)
	{
		HUD_.Add_HUD_Object(i);
	}
}

void HUD_Level::Update(float dt)
{
	h_cheese->SetScale(Application_.GetScreenSize());

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
		if(!HUD_.isHUDActive)
			HUD_.isHUDActive = true;
		int num = StateManager_.GetCurrentState()->GetCaptureLimit();
		std::string num_string = std::to_string(num);
		std::wstring temp = L"";
		temp.assign(num_string.begin(), num_string.end());
		h_capture_number->GetComponentByTemplate<Font>()->SetString(temp);

		h_capture_limit->SetVisible();
		h_capture_number->SetVisible();

		if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
		{
			IsOptionWindowOpen = !IsOptionWindowOpen;
			if (h_option_window->GetMesh().IsVisible())
			{
				h_option_window->GetMesh().Invisible();
				h_fullscreen_button->GetMesh().Invisible();
				h_bgm_scroll_bar->GetMesh().Invisible();
				h_sfx_scroll_bar->GetMesh().Invisible();
				h_bgm_scroll_button->GetMesh().Invisible();
				h_sfx_scroll_button->GetMesh().Invisible();
				h_mute_button->GetMesh().Invisible();
			}
			else
			{
				h_option_window->GetMesh().Visible();
				h_fullscreen_button->GetMesh().Visible();
				h_bgm_scroll_bar->GetMesh().Visible();
				h_sfx_scroll_bar->GetMesh().Visible();
				h_bgm_scroll_button->GetMesh().Visible();
				h_sfx_scroll_button->GetMesh().Visible();
				h_mute_button->GetMesh().Visible();
				StateManager_.Pause();
			}
		}

		if (IsOptionWindowOpen)
		{
			if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
			{
				h_select = Input::ClickHUDButton();

				if (h_select->GetComponentByTemplate<UI>() != nullptr)
				{
					if (h_select->GetComponentByTemplate<UI>()->GetId() == "fullscreen")
					{
						Application_.FullScreen();
					}

			/*		if (h_select->GetComponentByTemplate<UI>()->GetId() == "scrollbutton")
					{
						float save_x = Input::GetMousePos().x;
						float save_y = h_select->GetTransform().GetTranslation().y;
						h_select->SetTranslation({ save_x, save_y });
					}*/
				}
			}
		}
	}
	else
	{
		HUD_.isHUDActive = false;
	}
}

void HUD_Level::ShutDown()
{
	container.clear();
}

Object* HUD_Level::CreateHudButton(vector2 pos, vector2 scale, float depth, std::string path, std::string id)
{
	Object* button = new Object();

	button->SetTranslation(pos);
	button->SetScale(scale);
	button->SetDepth(depth);
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::HUD_Button);
	button->AddComponent(new Sprite(path));
	button->AddComponent(new UI(id));
	button->GetMesh().Invisible();

	return button;
}
