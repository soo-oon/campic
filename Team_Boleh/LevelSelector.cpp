#include "LevelSelector.hpp"
#include "UI.hpp"
#include "DepthValue.hpp"
#include "Button.hpp"

void LevelSelector::Initialize()
{
	m_Menu1 = new MenuPage();
	m_Menu2 = new MenuPage();
	m_Menu3 = new MenuPage();

	page_count = 1;
	m_LevelLock = LevelJson_.LoadLevelLock();

	mouse_icon = new Object();
	mouse_icon->SetTranslation({ 0,0 });
	mouse_icon->SetScale({ 50,50 });
	mouse_icon->SetDepth(-0.8f);
	mouse_icon->SetObjectType(ObjectType::None);
	mouse_icon->SetMesh(mesh::CreateBox());
	mouse_icon->AddComponent(new Sprite("asset/images/UI/MouseCursor.png"));
	Objectmanager_.AddObject(mouse_icon);

	background = new Object();
	background->SetTranslation({ 0, 0 });
	background->SetDepth(0.98f);
	background->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width + 100), static_cast<float>(Application_.GetGLFWvidmode()->height + 100) });
	background->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	background->SetObjectType(ObjectType::Button);
	background->AddComponent(new Animation("asset/images/Page/BackgroundDay.png", "day", 16, 0.15f, true));
	background->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Page/BackgroundAfernoon.png", "sunset", 16, 0.15f, true);
	background->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/Page/BackgroundNight.png", "night", 16, 0.15f, true);
	
	cam = new Object();
	cam->SetTranslation({ 0, 0 });
	cam->SetScale({ 1200,900 });
	cam->SetDepth(BACKGROUND);
	cam->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	cam->SetObjectType(ObjectType::Background);
	cam->AddComponent(new Sprite("asset/images/Objects/LevelSelect1.png"));

	CreateMenu1();
	for (auto& i : m_Menu1->GetButtons())
	{
		button_.AddObject(i);
	}

	previous = new Object();
	previous->SetTranslation({ -300, -293 });
	previous->SetScale({ 128,128 });
	previous->SetDepth(HUD_OBJECT2);
	previous->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	previous->SetObjectType(ObjectType::Button);
	previous->AddComponent(new Sprite("asset/images/UI/PrevButton.png"));
	previous->AddInitComponent(new UI("previous"));

	next = new Object();
	next->SetTranslation({ 200, -293 });
	next->SetScale({ 128,128 });
	next->SetDepth(HUD_OBJECT2);
	next->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	next->SetObjectType(ObjectType::Button);
	next->AddComponent(new Sprite("asset/images/UI/NextButton.png"));
	next->AddInitComponent(new UI("next"));

	Objectmanager_.AddObject(background);
	Objectmanager_.AddObject(cam);
        button_.AddObject(previous);
        button_.AddObject(next);

	button = new Object();
        button->SetTranslation({ 310.f, 300.f });
	button->SetScale({ 182,96 });
	button->SetDepth(HUD_BUTTON);
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::Button);
	button->AddInitComponent(new Sprite("asset/images/UI/Back.png"));
	button->AddInitComponent(new UI("back"));
	button_.AddObject(button);
}

void LevelSelector::Update(float dt)
{
	mouse_icon->SetTranslation(Input::GetMousePos());

	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		m_selectPage = Input::ClickObject(ObjectDepth::HUD_OBJECT2);

		if (m_selectPage)
		{
			if (m_selectPage->GetComponentByTemplate<UI>()->GetId() == "previous")
			{
				AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.1f);
				selectPage = !selectPage;

				if (page_count == 1)
					page_count = 3;
				else
					--page_count;
			}

			if (m_selectPage->GetComponentByTemplate<UI>()->GetId() == "next")
			{
				AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.1f);
				selectPage = !selectPage;

				if (page_count == 3)
					page_count = 1;
				else
					++page_count;
			}
		}
	}

	if (selectPage)
	{
		button_.RemoveContainer();

		switch (page_count)
		{
		case 1:
		{
			background->GetComponentByTemplate<Animation>()->ChangeAnimation("day");
			cam->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/Objects/LevelSelect1.png");
			m_Menu1->Clear();
			CreateMenu1();
			for (auto& i : m_Menu1->GetButtons())
			{
				button_.AddObject(i);
			}
                        CreateBackButton();
			selectPage = false;
			break;
		}
		case 2:
		{
			background->GetComponentByTemplate<Animation>()->ChangeAnimation("sunset");
			cam->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/Objects/LevelSelect2.png");				
			m_Menu2->Clear();
			CreateMenu2();
			for (auto& i : m_Menu2->GetButtons())
			{
				button_.AddObject(i);
			}
                        CreateBackButton();
			selectPage = false;
			break;
		}
		case 3:
		{
			background->GetComponentByTemplate<Animation>()->ChangeAnimation("night");
			cam->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/Objects/LevelSelect3.png");
			m_Menu3->Clear();
			CreateMenu3();
			for (auto& i : m_Menu3->GetButtons())
			{
				button_.AddObject(i);
			}
                        CreateBackButton();
			selectPage = false;
			break;
		}
		default:
			break;
		}
	}

	if (button_.IntersectionCheck(Input::GetMousePos()))
	{
            button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.1f);

			if(button_.GetSelect().first != previous && button_.GetSelect().first != next)
			{
				std::string temp = button_.GetSelect().first->GetComponentByTemplate<UI>()->GetId();

				if(temp == "Level1")
				{
					StateManager_.ToStartScene();
				}
				else if(temp == "back")
				{
					StateManager_.BackToMainMenu();
				}
				else
				{
					SetLevelIndicator(temp);
					ChangeLevel(temp);
				}
			}
                        else if(button_.GetSelect().first == previous)
                        {
                            AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.3f);
                            selectPage = !selectPage;

                            if (page_count == 1)
                                page_count = 3;
                            else
                                --page_count;
                        }
                        else if(button_.GetSelect().first == next)
                        {
                            AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.3f);
                            selectPage = !selectPage;

                            if (page_count == 3)
                                page_count = 1;
                            else
                                ++page_count;
                        }
		}
	}
        else
        {
            for(auto &i : button_.GetContainer())
            {
                i.get()->GetMesh().ChangeColor({ 255,255,255 });
            }
        }
}

void LevelSelector::ShutDown()
{
	m_Menu1->GetButtons().clear();
	m_Menu2->GetButtons().clear();
	m_Menu3->GetButtons().clear();
	button_.RemoveContainer();

	UnLoad();
}

void LevelSelector::CreateLevelButton(vector2 pos, vector2 scale, std::string level_text,  std::string level_id, std::string texture_level,MenuPage* menu)
{
	Object* button = new Object();
	button->SetTranslation(pos);
	button->SetScale(scale);
	button->SetDepth(HUD_OBJECT);
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::Button);

	auto isLocked = m_LevelLock.find(level_id)->second;
	button->AddComponent(new UI(level_text, isLocked));

	std::string path = "asset/images/UI/";
	path.append(texture_level);
	path.append(".png");

	button->AddComponent(new Sprite(path));
	if (!isLocked)
	{
		Object* lock = new Object();
		lock->SetTranslation(pos);
		lock->SetScale(scale-10.f);
		lock->SetDepth(HUD_OBJECT - 0.02f);
		lock->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
		lock->SetObjectType(ObjectType::Button);
		lock->AddComponent(new Sprite("asset/images/UI/Lock.png"));

		menu->InsertButtons(lock);
	}
	menu->InsertButtons(button);
}

void LevelSelector::CreateMenu1()
{
	std::string text = "Level";
	float base_y = 90.f;

	for (int i = 1, j = 1; i <= 6; ++i, ++j)
	{
		if (i == 4)
		{
			base_y -= 200;
			j = 1;
		}
		CreateLevelButton(vector2(-400.f + (185.f * j), base_y), vector2(150, 150), text + std::to_string(i), text + std::to_string(i), 
			text + std::to_string(i), m_Menu1);
		text = "Level";
	}
}

void LevelSelector::CreateMenu2()
{
	std::string text = "Level";
	float base_y = 90.f;

	for (int i = 1, j = 1; i <= 6; ++i, ++j)
	{
		if (i == 4)
		{
			base_y -= 200;
			j = 1;
		}
		CreateLevelButton(vector2(-400.f + (185.f * j), base_y), vector2(150, 150), text + std::to_string(i + 6), text + std::to_string(i + 6),
			text + std::to_string(i),m_Menu2);
		text = "Level";
	}
}

void LevelSelector::CreateMenu3()
{
	std::string text = "Level";
	float base_y = 90.f;

	for (int i = 1, j = 1; i <= 6; ++i, ++j)
	{
		if (i == 4)
		{
			base_y -= 200;
			j = 1;
		}
		CreateLevelButton(vector2(-400.f + (185.f * j), base_y), vector2(150, 150), text + std::to_string(i + 12),
			text + std::to_string(i + 12), text + std::to_string(i),m_Menu3);
		text = "Level";
	}
}

void LevelSelector::CreateBackButton()
{
    button = new Object();
    button->SetTranslation({ 310.f, 300.f });
    button->SetScale({ 182,96 });
    button->SetDepth(HUD_BUTTON);
    button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    button->SetObjectType(ObjectType::Button);
    button->AddInitComponent(new Sprite("asset/images/UI/Back.png"));
    button->AddInitComponent(new UI("back"));
    button_.AddObject(button);

    previous = new Object();
    previous->SetTranslation({ -300, -293 });
    previous->SetScale({ 128,128 });
    previous->SetDepth(HUD_OBJECT2);
    previous->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    previous->SetObjectType(ObjectType::Button);
    previous->AddComponent(new Sprite("asset/images/UI/PrevButton.png"));
    previous->AddInitComponent(new UI("previous"));

    next = new Object();
    next->SetTranslation({ 200, -293 });
    next->SetScale({ 128,128 });
    next->SetDepth(HUD_OBJECT2);
    next->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    next->SetObjectType(ObjectType::Button);
    next->AddComponent(new Sprite("asset/images/UI/NextButton.png"));
    next->AddInitComponent(new UI("next"));


    button_.AddObject(previous);
    button_.AddObject(next);
}


