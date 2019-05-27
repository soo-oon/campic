#include "HUD_Level.hpp"
#include "HUD.hpp"
#include "Capture.hpp"
#include "UI.hpp"
#include "ObjectDepth.hpp"
#include "Engine.hpp"

void HUD_Level::Initialize()
{
	h_chapter = new Object();
	h_chapter->SetTranslation({ static_cast<float>(Application_.GetGLFWvidmode()->width) / 7 - 350.f, static_cast<float>(Application_.GetGLFWvidmode()->height) / 2 - 100.f });
	h_chapter->SetScale({ 2.8f });
	h_chapter->SetDepth(-0.5f);
	h_chapter->AddComponent(new Font(L"asset/font/sansation.fnt", L"0"));
	h_chapter->GetComponentByTemplate<Font>()->SetFillColor(Colors::Black);
	h_chapter->SetInvisible();
	h_chapter->GetMesh().Invisible();
	HUD_.Add_HUD_Object(h_chapter);

	h_capture_limit = new Object();
	h_capture_limit->SetTranslation({ static_cast<float>(Application_.GetGLFWvidmode()->width)/2 -250.f, static_cast<float>(Application_.GetGLFWvidmode()->height)/2 -70.f});
	h_capture_limit->SetScale(vector2{ screen_size.x /10.f, screen_size.y/10.f });
	h_capture_limit->SetDepth(-0.5f);
	h_capture_limit->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	h_capture_limit->SetObjectType(ObjectType::None);
	h_capture_limit->AddInitComponent(new Sprite("asset/images/UI/CaptureLimitBlack.png"));
	h_capture_limit->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/CaptureLimitWhite.png");
	h_capture_limit->SetInvisible();
	h_capture_limit->GetMesh().Invisible();
	HUD_.Add_HUD_Object(h_capture_limit);

	h_capture_number = new Object();
	h_capture_number->SetTranslation({ static_cast<float>(Application_.GetGLFWvidmode()->width)/2 - 170.f, static_cast<float>(Application_.GetGLFWvidmode()->height)/2 -110.f});
	h_capture_number->SetScale({ 2.8f });
	h_capture_number->SetDepth(-0.5f);
	h_capture_number->AddComponent(new Font(L"asset/font/sansation.fnt", L"0"));
	h_capture_number->GetComponentByTemplate<Font>()->SetFillColor(Colors::Black);
	h_capture_number->SetInvisible();
	h_capture_number->GetMesh().Invisible();
	HUD_.Add_HUD_Object(h_capture_number);

	h_cheese = new Object();
	h_cheese->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	h_cheese->SetDepth(-0.5f);
	h_cheese->SetMesh(mesh::CreateBox(1, Colors::Yellow));
	h_cheese->SetObjectType(ObjectType::Background);
	h_cheese->SetInvisible();
	h_cheese->GetMesh().Invisible();
	HUD_.Add_HUD_Object(h_cheese);

	////////////OPTION WINDOW
	h_option_window = new Object();
	h_option_window->SetScale({ screen_size.x, screen_size.y});
	h_option_window->SetDepth(-0.6f);
	h_option_window->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	h_option_window->SetObjectType(ObjectType::None);
	h_option_window->AddComponent(new Sprite("asset/images/Page/OptionPage.png"));
	h_option_window->GetMesh().Invisible();
	HUD_.Add_HUD_Object(h_option_window);

	h_volume_scroll_button = CreateHudButton(vector2(screen_size.x - 1300.f, screen_size.y - 890.f), screen_size / 25.f,
		HUD_BUTTON, "asset/images/UI/Icon_AdjustBall.png", "volume_button");
	HUD_.Add_HUD_Object(h_volume_scroll_button);

	h_restart_button = CreateHudButton(vector2(screen_size.x - 1000.f, screen_size.y - 800.f), screen_size / 10.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "restart");
	HUD_.Add_HUD_Object(h_restart_button);

	h_mute_button = CreateHudButton(vector2(screen_size.x - 1000.f, screen_size.y - 1000.f), screen_size / 10.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "Mute");
	HUD_.Add_HUD_Object(h_mute_button);

	h_fullscreen_button = CreateHudButton(vector2(screen_size.x - 1000.f, screen_size.y - 1100.f), screen_size / 10.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "fullscreen");
	HUD_.Add_HUD_Object(h_fullscreen_button);

	h_backtomenu_button = CreateHudButton(vector2(screen_size.x - 1000.f, screen_size.y - 1200.f), screen_size / 10.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "backtomenu");
	HUD_.Add_HUD_Object(h_backtomenu_button);

	h_quit_button = CreateHudButton(vector2(screen_size.x - 1000.f, screen_size.y - 1300.f), screen_size / 10.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "quit");
	HUD_.Add_HUD_Object(h_quit_button);
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
		if (!HUD_.isHUDActive)
			HUD_.isHUDActive = true;

		int num = StateManager_.GetCurrentState()->GetCaptureLimit();
		std::string num_string = std::to_string(num);
		std::wstring temp = L"";
		temp.assign(num_string.begin(), num_string.end());
		h_capture_number->GetComponentByTemplate<Font>()->SetString(temp);

		h_capture_limit->SetVisible();
		h_capture_number->SetVisible();

		if (StateManager_.GetCurrentState()->GetChapter().first == 3)
		{
			h_capture_limit->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/CaptureLimitWhite.png");
			h_chapter->GetComponentByTemplate<Font>()->SetFillColor(Colors::White);
			h_capture_number->GetComponentByTemplate<Font>()->SetFillColor(Colors::White);
		}
		else
		{
			h_capture_limit->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/CaptureLimitBlack.png");
			h_chapter->GetComponentByTemplate<Font>()->SetFillColor(Colors::Black);
			h_capture_number->GetComponentByTemplate<Font>()->SetFillColor(Colors::Black);
		}

		std::pair<int,int> chap = StateManager_.GetCurrentState()->GetChapter();
		std::string chap_string = std::to_string(chap.first);
		chap_string.append("-");
		chap_string.append(std::to_string(chap.second));

		std::wstring temp1 = L"";
		temp1.assign(chap_string.begin(), chap_string.end());
		h_chapter->GetComponentByTemplate<Font>()->SetString(temp1);

		h_chapter->SetVisible();
	}
	else
	{
		h_capture_limit->SetInvisible();
		h_capture_number->SetInvisible();
		h_chapter->SetInvisible();
	}

	if (StateManager_.GetCurrentState()->GetCurrentStateInfo() != State_Information::Splash)
	{
		if(!HUD_.isHUDActive)
			HUD_.isHUDActive = true;

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
							}
							else
							{
								h_select->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/ButtonOff.png");
							}
						}
					}

					if (h_select->GetComponentByTemplate<UI>() != nullptr)
					{
						if (h_select->GetComponentByTemplate<UI>()->GetId() == "restart")
						{
							IsOptionWindowOpen = !IsOptionWindowOpen;
							StateManager_.TogglePause();
							StateManager_.ChangeStage();
						}
					}

					if (h_select->GetComponentByTemplate<UI>() != nullptr)
					{
						if (h_select->GetComponentByTemplate<UI>()->GetId() == "backtomenu")
						{
							IsOptionWindowOpen = !IsOptionWindowOpen;
							StateManager_.TogglePause();
							StateManager_.BackToMainMenu();
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
	UnLoad();
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
