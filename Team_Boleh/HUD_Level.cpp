#include "HUD_Level.hpp"
#include "HUD.hpp"
#include "Capture.hpp"
#include "UI.hpp"
#include "ObjectDepth.hpp"
#include "Engine.hpp"
#include <iostream>

void HUD_Level::Initialize()
{
	h_capture_limit = new Object();
	h_capture_limit->SetTranslation(vector2(screen_size.x/2.f -200.f, screen_size.y / 2.f - 100.f));
	h_capture_limit->SetScale(vector2{ screen_size.x /10.f, screen_size.y/10.f });
	h_capture_limit->SetDepth(-0.5f);
	h_capture_limit->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	h_capture_limit->SetObjectType(ObjectType::None);
	h_capture_limit->AddInitComponent(new Sprite("asset/images/UI/CaptureLimit.png"));
	h_capture_limit->SetInvisible();
	h_capture_limit->GetMesh().Invisible();
	container.push_back(h_capture_limit);

	h_capture_number = new Object();
	h_capture_number->SetTranslation(vector2(screen_size.x/2.f -130.f , 340.f));
	h_capture_number->SetScale({ 2.8 });
	h_capture_number->SetDepth(-0.5f);
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
	h_option_window->SetScale({ screen_size.x, screen_size.y});
	h_option_window->SetDepth(-0.6f);
	h_option_window->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	h_option_window->SetObjectType(ObjectType::None);
	h_option_window->AddComponent(new Sprite("asset/images/OptionPage.png"));
	h_option_window->GetMesh().Invisible();

	h_volume_scroll_button = CreateHudButton(vector2(screen_size.x - 1300.f, screen_size.y - 890.f), screen_size / 25.f,
		HUD_BUTTON, "asset/images/UI/Icon_AdjustBall.png", "volume_button");

	h_fullscreen_button = new Object();
	h_fullscreen_button->SetTranslation(vector2(screen_size.x-1200, screen_size.y-1000));
	h_fullscreen_button->SetScale(screen_size/10);
	h_fullscreen_button->SetDepth(HUD_BUTTON);
	h_fullscreen_button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	h_fullscreen_button->SetObjectType(ObjectType::HUD_Button);
	h_fullscreen_button->AddComponent(new Sprite("asset/images/UI/EmptyBox.png"));
	h_fullscreen_button->AddComponent(new UI("fullscreen"));
	h_fullscreen_button->GetMesh().Invisible();
	
	capture_camera = new Object();
	capture_camera->SetTranslation({0,0});
	capture_camera->SetScale({ 300,150 });
	capture_camera->SetDepth(-0.3f);
	capture_camera->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	capture_camera->SetObjectType(ObjectType::Capture_Camera_main);
	capture_camera->AddInitComponent(new Animation("asset/images/camera_frame.png", "basic_camera", 2, 0.5, true));
	capture_camera->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/cheese.png", "cheese", 2, 0.5, true);
	capture_camera->AddInitComponent(new Capture({}));
	capture_camera->GetComponentByTemplate<Capture>()->SetInvisibleCaptureObj();

	h_restart_button = CreateHudButton(vector2(screen_size.x - 1000.f, screen_size.y - 800.f), screen_size / 10.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "restart");

	h_mute_button = CreateHudButton(vector2(screen_size.x - 1000.f, screen_size.y - 1000.f), screen_size / 10.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "Mute");

	h_fullscreen_button = CreateHudButton(vector2(screen_size.x - 1000.f, screen_size.y - 1100.f), screen_size / 10.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "fullscreen");

	h_backtomenu_button = CreateHudButton(vector2(screen_size.x - 1000.f, screen_size.y - 1200.f), screen_size / 10.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "backtomenu");

	h_quit_button = CreateHudButton(vector2(screen_size.x - 1000.f, screen_size.y - 1300.f), screen_size / 10.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "quit");

	container.push_back(h_option_window);
	container.push_back(h_fullscreen_button);
	container.push_back(h_volume_scroll_button);
	container.push_back(h_mute_button);
	container.push_back(h_restart_button);
	container.push_back(h_backtomenu_button);
	container.push_back(h_quit_button);

	for(auto& i : container)
	{
		HUD_.Add_HUD_Object(i);
	}
	HUD_.Add_HUD_Object(h_capture_number);
	HUD_.Add_HUD_Object(h_fullscreen_button);
	HUD_.Add_HUD_Object(h_capture_limit);
	HUD_.Add_HUD_Object(h_cheese);
	HUD_.Add_HUD_Object(h_option_window);
	HUD_.Add_HUD_Object(capture_camera);
}

void HUD_Level::Update(float dt)
{
	if(Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_RIGHT))
	{
		std::cout << "(" << Input::GetMousePos().x << "," << Input::GetMousePos().y << ")" << std::endl;
	}

	if (!is_game_state)
	{
		if (HUD_.Get_Current_Game_State() != nullptr)
		{
			is_game_state = true;
			capture_camera->GetComponentByTemplate<Capture>()->SetResetPosition(HUD_.Get_Current_Game_State()->GetStartPosition());
			Objectmanager_.SetCaptureObject(capture_camera);
		}
	}
	else
	{
		if (!capture_camera->GetComponentByTemplate<Capture>()->IsCaputreObjectVisible())
			capture_camera->GetComponentByTemplate<Capture>()->SetVisibleCaptureObj();
	}

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

				h_cheese->GetMesh().Decrease_Alpha(10.f);

				if (h_cheese->GetMesh().GetColor(0).Alpha <= 15.f)
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
		}

		if (IsOptionWindowOpen)
		{
			StateManager_.Pause();

			h_option_window->GetMesh().Visible();
			h_fullscreen_button->GetMesh().Visible();
			h_volume_scroll_button->GetMesh().Visible();
			h_restart_button->GetMesh().Visible();
			h_quit_button->GetMesh().Visible();
			h_backtomenu_button->GetMesh().Visible();
			h_mute_button->GetMesh().Visible();

			float volume = 0.f;
			h_select = Input::ClickHUDButton();

			if (h_select != nullptr)
			{
				if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
				{
					if (h_select->GetComponentByTemplate<UI>() != nullptr)
					{
						if (h_select->GetComponentByTemplate<UI>()->GetId() == "fullscreen")
						{
							fullscreen = !fullscreen;
							Application_.FullScreen();
							if (fullscreen)
							{
								h_select->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/ButtonOn.png");
							}
							else
							{
								h_select->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/ButtonOff.png");
							}
							h_select = nullptr;
						}
					}

					if (h_select->GetComponentByTemplate<UI>() != nullptr)
					{
						if (h_select->GetComponentByTemplate<UI>()->GetId() == "Mute")
						{
							mute = !mute;
							AudioManager_.GetMasterChannel()->setMute(mute);
							if(mute)
							{
								h_select->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/ButtonOn.png");
								h_select = nullptr;
							}
							else
							{
								h_select->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/ButtonOff.png");
								h_select = nullptr;
							}
						}
					}

					if (h_select->GetComponentByTemplate<UI>() != nullptr)
					{
						if (h_select->GetComponentByTemplate<UI>()->GetId() == "restart")
						{
							IsOptionWindowOpen = !IsOptionWindowOpen;
							StateManager_.TogglePause();
							UnLoad();
							StateManager_.ChangeStage();
							h_select = nullptr;
						}
					}

					if (h_select->GetComponentByTemplate<UI>() != nullptr)
					{
						if (h_select->GetComponentByTemplate<UI>()->GetId() == "backtomenu")
						{
							IsOptionWindowOpen = !IsOptionWindowOpen;
							StateManager_.TogglePause();
							StateManager_.BackToMenu();
							h_select = nullptr;
						}
					}

					if (h_select->GetComponentByTemplate<UI>() != nullptr)
					{
						if (h_select->GetComponentByTemplate<UI>()->GetId() == "quit")
						{
							Engine::IsQuit = true;
						}
					}
				}

				if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_LEFT))
				{
					if (h_select->GetComponentByTemplate<UI>() != nullptr)
					{
						if (h_select->GetComponentByTemplate<UI>()->GetId() == "volume_button")
						{
							float save_x = Input::GetMousePos().x;
							static float save_y = h_select->GetTransform().GetTranslation().y;

							volume = (100.f / (320.f - -240.f)*save_x) - ((100 * -240.f) / (320.f - -240.f));

							if (volume < 0.f)
								volume = 0.f;
							else if (volume > 100.f)
								volume = 100.f;

							if (save_x > -220.f && save_x < 165.f)
							{
								h_select->SetTranslation({ save_x, save_y });
							}
							AudioManager_.SetMasterVolume(volume / 100.f);
						}
					}
				}
			}
		}
		else
		{
			h_option_window->GetMesh().Invisible();
			h_fullscreen_button->GetMesh().Invisible();
			h_volume_scroll_button->GetMesh().Invisible();
			h_restart_button->GetMesh().Invisible();
			h_quit_button->GetMesh().Invisible();
			h_backtomenu_button->GetMesh().Invisible();
			h_mute_button->GetMesh().Invisible();
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
