#include "LevelSelector.hpp"
#include "UI.hpp"
#include "DepthValue.hpp"
#include <iostream>

void LevelSelector::Initialize()
{
	m_Menu1 = new MenuPage();
	m_Menu2 = new MenuPage();

	m_LevelLock = LevelJson_.LoadLevelLock();
	mouse_icon = new Object();
	mouse_icon->SetTranslation({ 0,0 });
	mouse_icon->SetScale({ 50,50 });
	mouse_icon->SetDepth(depth::NearDepth);
	mouse_icon->SetObjectType(ObjectType::None);
	mouse_icon->SetMesh(mesh::CreateBox());
	mouse_icon->AddComponent(new Sprite("asset/images/UI/MouseCursor.png"));

	Object* background = new Object();
	background->SetTranslation({ -0, 0 });
	background->SetScale({ 1200,900 });
	background->SetDepth(BACKGROUND);
	background->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	background->SetObjectType(ObjectType::Background);
	background->AddComponent(new Sprite("asset/images/Page/LevelSelect.png"));

	CreateMenuPage();

	Object* previous = new Object();
	previous->SetTranslation({ -300, -293 });
	previous->SetScale({ 128,128 });
	previous->SetDepth(HUD_BUTTON);
	previous->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	previous->SetObjectType(ObjectType::Button);
	previous->AddComponent(new Sprite("asset/images/UI/PrevButton.png"));
	previous->AddComponent(new UI("previous"));
	Objectmanager_.AddObject(previous);

	Object* next = new Object();
	next->SetTranslation({ 200, -293 });
	next->SetScale({ 128,128 });
	next->SetDepth(HUD_BUTTON);
	next->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	next->SetObjectType(ObjectType::Button);
	next->AddComponent(new Sprite("asset/images/UI/NextButton.png"));
	next->AddComponent(new UI("next"));
	Objectmanager_.AddObject(next);

	for(auto& i : m_Menu1->GetButtons())
	{
		Objectmanager_.AddObject(i);
	}
	for (auto& i : m_Menu2->GetButtons())
	{
		Objectmanager_.AddObject(i);
	}
	Objectmanager_.AddObject(mouse_icon);
	Objectmanager_.AddObject(background);
}

void LevelSelector::Update(float dt)
{
	mouse_icon->SetTranslation(Input::GetMousePos());
	if(selectPage)
	{
		for (auto& i : m_Menu1->GetButtons())
		{
			i->GetMesh().Visible();
		}
		for (auto& i : m_Menu2->GetButtons())
		{
			i->GetMesh().Invisible();
		}
	}
	else
	{
		for (auto& i : m_Menu2->GetButtons())
		{
			i->GetMesh().Visible();
		}
		for (auto& i : m_Menu1->GetButtons())
		{
			i->GetMesh().Invisible();
		}
	}

	if(Input::IsKeyTriggered(GLFW_KEY_LEFT))
	{
		selectPage = !selectPage;
	}
	if (Input::IsKeyTriggered(GLFW_KEY_RIGHT))
	{
		selectPage = !selectPage;
	}
	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		m_SelectLevel = Input::ClickObject(ObjectDepth::HUD_OBJECT);

		if (m_SelectLevel)
		{
			if(m_SelectLevel->GetComponentByTemplate<UI>()->GetIsLock())
			{
				SetLevelIndicator(m_SelectLevel->GetComponentByTemplate<UI>()->GetId());
				ChangeLevel(level_indicator);
			}
		}

		m_selectPage = Input::ClickObject(ObjectDepth::HUD_BUTTON);

		if (m_selectPage)
		{
			if (m_selectPage->GetComponentByTemplate<UI>()->GetId() == "previous")
				selectPage = !selectPage;

			if (m_selectPage->GetComponentByTemplate<UI>()->GetId() == "next")
				selectPage = !selectPage;
		}
	}

	if (Input::IsKeyTriggered(GLFW_KEY_F10))
	{
		LevelJson_.CreateLevelLockDocument();
	}
}

void LevelSelector::ShutDown()
{
	m_Menu1->GetButtons().clear();
	m_Menu2->GetButtons().clear();
	delete m_Menu1;
	delete m_Menu2;
	UnLoad();
}

void LevelSelector::CreateLevelButton(vector2 pos, vector2 scale, std::string level_text,  std::string level_id, MenuPage* menu)
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
	path.append(level_id);
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

void LevelSelector::CreateMenuPage()
{
	std::string text = "Level";
	float base_y = 70.f;

	for (int i = 1, j = 1; i <= 10; ++i, ++j)
	{
		if (i == 6)
		{
			base_y -= 200;
			j = 1;
		}
		CreateLevelButton(vector2(-600.f + (185.f*j), base_y), vector2(150, 150), text + std::to_string(i), text + std::to_string(i), m_Menu1);
		text = "Level";
	}

	base_y = 70.f;
	for (int i = 1, j = 1; i <= 10; ++i, ++j)
	{
		if (i == 6)
		{
			base_y -= 200;
			j = 1;
		}
		CreateLevelButton(vector2(-600.f + (185.f*j), base_y), vector2(150, 150), text + std::to_string(i+10), text + std::to_string(i+10), m_Menu2);
		text = "Level";
	}
}


