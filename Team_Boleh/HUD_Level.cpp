#include "HUD_Level.hpp"
#include "HUD.hpp"
#include "Capture.hpp"
#include "UI.hpp"
#include "ObjectDepth.hpp"
#include "Engine.hpp"
#include "DepthValue.hpp"
#include "Button.hpp"

void HUD_Level::Initialize()
{
	mouse_icon = new Object();
	mouse_icon->SetTranslation({ 0,0 });
	mouse_icon->SetScale({ 50,50 });
	mouse_icon->SetDepth(depth::NearDepth- 0.09f);
	mouse_icon->SetObjectType(ObjectType::None);
	mouse_icon->SetMesh(mesh::CreateBox());
	mouse_icon->AddComponent(new Sprite("asset/images/UI/MouseCursor.png"));
	HUD_.Add_HUD_Object(mouse_icon);

	h_capture_limit = new Object();
	h_capture_limit->SetTranslation({ -80.0f, -static_cast<float>(Application_.GetGLFWvidmode()->height)/2 + 90.0f});
	h_capture_limit->SetScale(vector2{ 250, 150 });
	h_capture_limit->SetDepth(-0.89f);
	h_capture_limit->SetMesh(mesh::CreateBox());
	h_capture_limit->AddInitComponent(new Sprite("asset/images/UI/CaptureLimit.png"));
	h_capture_limit->AddInitComponent(new Particle_Generator(15, 2.0f, 3.0f, 5.0f, {0,3}, {-3,3}, {35,35}, {}, {"asset/images/UI/CaptureLimitRipped.png"}, false));
	h_capture_limit->GetComponentByTemplate<Particle_Generator>()->SetParticle_Fire_Type(Particle_Fire_Type::Divergent);
	h_capture_limit->SetInvisible();
	h_capture_limit->GetMesh().Invisible();
	HUD_.Add_HUD_Object(h_capture_limit);

	m_capture_one_digits = new Object();
	m_capture_one_digits->SetDepth(-0.89f);
	m_capture_one_digits->SetScale({180, 120});
	m_capture_one_digits->SetTranslation({ 180.0f, -static_cast<float>(Application_.GetGLFWvidmode()->height) / 2 + 90.0f });
	m_capture_one_digits->AddComponent(new Sprite());
	m_capture_one_digits->SetInvisible();
	m_capture_one_digits->SetMesh(mesh::CreateBox(1, {0,255,0}));
	HUD_.Add_HUD_Object(m_capture_one_digits);

	m_capture_double_digits = new Object();
	m_capture_double_digits->SetDepth(-0.89f);
	m_capture_double_digits->SetScale({ 180, 120 });
	m_capture_double_digits->SetTranslation({ 100.0f, -static_cast<float>(Application_.GetGLFWvidmode()->height) / 2 + 90.0f });
	m_capture_double_digits->AddComponent(new Sprite());
	m_capture_double_digits->SetInvisible();
	m_capture_double_digits->SetMesh(mesh::CreateBox(1, { 0,255,0 }));
	HUD_.Add_HUD_Object(m_capture_double_digits);

	m_capture_underbar = new Object();
	m_capture_underbar->SetDepth(-0.89f);
	m_capture_underbar->SetScale({ 80, 80 });
	m_capture_underbar->SetTranslation({ 0, static_cast<float>(Application_.GetGLFWvidmode()->height) / 2 - 70.f });
	m_capture_underbar->AddComponent(new Sprite("asset/images/UI/UnderBar.png"));
	m_capture_underbar->SetInvisible();
	m_capture_underbar->SetMesh(mesh::CreateBox(1, { 130,254,49 }));
	HUD_.Add_HUD_Object(m_capture_underbar);

	m_capture_base_num = new Object();
	m_capture_base_num->SetDepth(-0.89f);
	m_capture_base_num->SetScale({ 80, 80 });
	m_capture_base_num->SetTranslation({ m_capture_underbar->GetTransform().GetTranslation().x - 80
		, static_cast<float>(Application_.GetGLFWvidmode()->height) / 2 - 70.f });
	m_capture_base_num->AddComponent(new Sprite());
	m_capture_base_num->SetInvisible();
	m_capture_base_num->SetMesh(mesh::CreateBox(1, { 130,254,49 }));
	HUD_.Add_HUD_Object(m_capture_base_num);

	m_capture_sub_num = new Object();
	m_capture_sub_num->SetDepth(-0.89f);
	m_capture_sub_num->SetScale({ 80, 80 });
	m_capture_sub_num->SetTranslation({ m_capture_underbar->GetTransform().GetTranslation().x + 80
		, static_cast<float>(Application_.GetGLFWvidmode()->height) / 2 - 70.f });
	m_capture_sub_num->AddComponent(new Sprite());
	m_capture_sub_num->SetInvisible();
	m_capture_sub_num->SetMesh(mesh::CreateBox(1, { 130,254,49 }));
	HUD_.Add_HUD_Object(m_capture_sub_num);

	UIBar[0] = new Object();
	UIBar[0]->SetDepth(-0.89f);
	UIBar[0]->SetMesh(mesh::CreateBox());
	UIBar[0]->SetInvisible();
	UIBar[0]->AddComponent(new Sprite("asset/images/UI/UIBAR.png"));
	UIBar[0]->SetTranslation({ 0, static_cast<float>(Application_.GetGLFWvidmode()->height) / 2 - 70.f });
	UIBar[0]->SetScale({ 280, 130 });
	HUD_.Add_HUD_Object(UIBar[0]);

	UIBar[1] = new Object();
	UIBar[1]->SetDepth(-0.89f);
	UIBar[1]->SetMesh(mesh::CreateBox());
	UIBar[1]->SetInvisible();
	UIBar[1]->AddComponent(new Sprite("asset/images/UI/UIBAR.png"));
	UIBar[1]->SetTranslation({ 0.0f, -static_cast<float>(Application_.GetGLFWvidmode()->height) / 2 + 90.0f });
	UIBar[1]->SetScale({ 600, 200 });
	HUD_.Add_HUD_Object(UIBar[1]);

	h_cheese = new Object();
	h_cheese->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width + 100), static_cast<float>(Application_.GetGLFWvidmode()->height + 100) });
	h_cheese->SetDepth(-0.89f);
	h_cheese->SetMesh(mesh::CreateBox(1, Colors::Yellow));
	h_cheese->SetObjectType(ObjectType::Background);
	h_cheese->SetInvisible();
	h_cheese->GetMesh().Invisible();
	HUD_.Add_HUD_Object(h_cheese);

	////////////OPTION WINDOW
	h_option_window = new Object();
	h_option_window->SetScale({ 1200,900 });
	h_option_window->SetDepth(-0.90f);
	h_option_window->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	h_option_window->SetObjectType(ObjectType::None);
	h_option_window->AddComponent(new Sprite("asset/images/Page/OptionPage.png"));
	h_option_window->GetMesh().Invisible();
	HUD_.Add_HUD_Object(h_option_window);

	h_volume_scroll_button = CreateHudButton(vector2(Application_.GetScreenSize().x - 1950.f, Application_.GetScreenSize().y - 921.f), Application_.GetScreenSize() / 29.f,
		HUD_BUTTON, "asset/images/UI/Icon_AdjustBall.png", "volume_button");
	HUD_.Add_HUD_Button(h_volume_scroll_button);

	h_mute_button = CreateHudButton(vector2(Application_.GetScreenSize().x - 1600.f, Application_.GetScreenSize().y - 1050.f), Application_.GetScreenSize() / 12.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "Mute");
	HUD_.Add_HUD_Button(h_mute_button);

	h_fullscreen_button = CreateHudButton(vector2(Application_.GetScreenSize().x - 1600.f, Application_.GetScreenSize().y - 1160.f), Application_.GetScreenSize() / 12.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "fullscreen");
	HUD_.Add_HUD_Button(h_fullscreen_button);

	h_backtomenu_button = CreateHudButton(vector2(Application_.GetScreenSize().x - 1600.f, Application_.GetScreenSize().y - 1280.f), Application_.GetScreenSize() / 12.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "backtomenu");
	HUD_.Add_HUD_Button(h_backtomenu_button);

	h_quit_button = CreateHudButton(vector2(Application_.GetScreenSize().x - 1600.f, Application_.GetScreenSize().y - 1390.f), Application_.GetScreenSize() / 12.f,
		HUD_BUTTON, "asset/images/UI/ButtonOff.png", "quit");
	HUD_.Add_HUD_Button(h_quit_button);
}

void HUD_Level::Update(float dt)
{
	mouse_icon->SetTranslation(Input::GetMousePos());

	if (StateManager_.GetCurrentState()->GetCurrentStateInfo() == State_Information::Menu || IsOptionWindowOpen)
		mouse_icon->SetVisible();
	else
		mouse_icon->SetInvisible();

	if(Capture::IsChangeCaptureCount)
	{
		SetCaptureNumberSprite(m_capture_one_digits, m_capture_double_digits);
		Capture::IsChangeCaptureCount = false;
	}

	if(is_active_particle)
	{
		m_dt += dt;

		if (m_dt > 1.0f)
		{
			h_capture_limit->GetComponentByTemplate<Particle_Generator>()->SetActiveCondition(false);
			is_active_particle = false;
			m_dt = 0.0f;
		}
	}

	if(HUD_.IsChangeGameLevel())
	{
		SetCapterNumberSprite(m_capture_base_num, m_capture_sub_num);
		HUD_.SetIsChangeGameLevel(false);
	}

	if(StateManager_.GetCurrentState()->GetCaptureObjectPointer() != nullptr)
	{
		if(auto cheese = StateManager_.GetCurrentState()->GetCaptureObjectPointer()->GetComponentByTemplate<Capture>();
			cheese != nullptr)
		{
			if (cheese->IsCheese())
			{
				is_active_particle = true;
				h_capture_limit->GetComponentByTemplate<Particle_Generator>()->SetActiveCondition(true);

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

		h_capture_limit->SetVisible();
		m_capture_one_digits->SetVisible();
		m_capture_double_digits->SetVisible();
		UIBar[0]->SetVisible();
		UIBar[1]->SetVisible();

		m_capture_underbar->SetVisible();
		m_capture_base_num->SetVisible();
		m_capture_sub_num->SetVisible();
	}
	else
	{
		h_capture_limit->SetInvisible();
		m_capture_one_digits->SetInvisible();
		m_capture_double_digits->SetInvisible();
		UIBar[0]->SetInvisible();
		UIBar[1]->SetInvisible();

		m_capture_underbar->SetInvisible();
		m_capture_base_num->SetInvisible();
		m_capture_sub_num->SetInvisible();
	}

	if (StateManager_.GetCurrentState()->GetCurrentStateInfo() != State_Information::Splash &&
		StateManager_.GetCurrentState()->GetCurrentStateInfo() != State_Information::CutScene &&
		StateManager_.GetCurrentState()->GetCurrentStateInfo() != State_Information::Credit && 
		StateManager_.GetCurrentState()->GetCurrentStateInfo() != State_Information::HowToPlay)
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
			h_capture_limit->GetComponentByTemplate<Particle_Generator>()->SetActiveCondition(false);
			h_option_window->GetMesh().Visible();
			h_fullscreen_button->GetMesh().Visible();
			h_volume_scroll_button->GetMesh().Visible();
			h_quit_button->GetMesh().Visible();
			h_backtomenu_button->GetMesh().Visible();
			h_mute_button->GetMesh().Visible();

			float volume = 0.f;
		
			if (HUD_.HUDIntersectionCheck(Input::GetMousePos()))
			{
				if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
				{
					std::string temp = HUD_.GetHUDSelect().first->GetComponentByTemplate<UI>()->GetId();
					if (temp == "fullscreen")
					{
						fullscreen = !fullscreen;
						Application_.FullScreen();
						if (fullscreen)
						{
							HUD_.GetHUDSelect().first->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/ButtonOn.png");
						}
						else
						{
							HUD_.GetHUDSelect().first->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/ButtonOff.png");
						}
					}

					if (temp == "Mute")
					{
						mute = !mute;
						AudioManager_.GetMasterChannel()->setMute(mute);
						if (mute)
						{
							HUD_.GetHUDSelect().first->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/ButtonOn.png");
						}
						else
						{
							HUD_.GetHUDSelect().first->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/ButtonOff.png");
						}
					}
					
					if (temp == "backtomenu")
					{
						IsOptionWindowOpen = !IsOptionWindowOpen;
						StateManager_.TogglePause();
						StateManager_.BackToMainMenu();
					}
					
					if (temp == "quit")
					{
						Engine::IsQuit = true;
					}
				}

				if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_LEFT))
				{
					std::string temp = HUD_.GetHUDSelect().first->GetComponentByTemplate<UI>()->GetId();
					if (temp == "volume_button")
					{
						float save_x = Input::GetMousePos().x;
						static float save_y = HUD_.GetHUDSelect().first->GetTransform().GetTranslation().y;

						volume = 100 * (save_x + 210.f) / 365.f;

						if (volume < 0.f)
							volume = 0.f;
						else if (volume > 100.f)
							volume = 100.f;

						if (save_x > -210.f && save_x < 155.f)
						{
							HUD_.GetHUDSelect().first->SetTranslation({ save_x, save_y });
						}
						AudioManager_.SetMasterVolume(volume / 100.f);
					}
					
				}
			}
		}
		else
		{
			h_option_window->GetMesh().Invisible();
			h_fullscreen_button->GetMesh().Invisible();
			h_volume_scroll_button->GetMesh().Invisible();
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
	button->SetDepth(-0.92f);
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::HUD_Button);
	button->AddComponent(new Sprite(path));
	button->AddComponent(new UI(id));
	button->GetMesh().Invisible();

	return button;
}

void HUD_Level::SetCaptureNumberSprite(Object* one_, Object* double_)
{
	int number = StateManager_.GetCurrentState()->GetCaptureLimit();

	int double_digits = number / 10;
	int one_digipts = number % 10;

	switch (one_digipts)
	{
	case 0:
		one_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number0.png");
		break;
	case 1:
		one_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number1.png");
		break;
	case 2:
		one_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number2.png");
		break;
	case 3:
		one_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number3.png");
		break;
	case 4:
		one_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number4.png");
		break;
	case 5:
		one_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number5.png");
		break;
	case 6:
		one_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number6.png");
		break;
	case 7:
		one_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number7.png");
		break;
	case 8:
		one_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number8.png");
		break;
	case 9:
		one_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number9.png");
		break;
	default:
		break;
	}

	switch (double_digits)
	{
	case 0:
		double_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number0.png");
		break;
	case 1:
		double_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number1.png");
		break;
	case 2:
		double_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number2.png");
		break;
	case 3:
		double_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number3.png");
		break;
	case 4:
		double_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number4.png");
		break;
	case 5:
		double_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number5.png");
		break;
	case 6:
		double_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number6.png");
		break;
	case 7:
		double_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number7.png");
		break;
	case 8:
		double_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number8.png");
		break;
	case 9:
		double_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number9.png");
		break;
	default:
		break;
	}
}

void HUD_Level::SetCapterNumberSprite(Object* base_, Object* sub_)
{
	int base = StateManager_.GetCurrentState()->GetChapter().first;
	int sub = StateManager_.GetCurrentState()->GetChapter().second;

	switch (base)
	{
	case 1:
		base_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number1.png");
		break;
	case 2:
		base_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number2.png");
		break;
	case 3:
		base_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number3.png");
		break;
	default:
		break;
	}

	switch (sub)
	{
	case 1:
		sub_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number1.png");
		break;
	case 2:
		sub_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number2.png");
		break;
	case 3:
		sub_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number3.png");
		break;
	case 4:
		sub_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number4.png");
		break;
	case 5:
		sub_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number5.png");
		break;
	case 6:
		sub_->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/UI/Number6.png");
		break;
	default:
		break;
	}
}
