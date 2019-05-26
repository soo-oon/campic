#include "LevelSelector.hpp"
#include "UI.hpp"

void LevelSelector::Initialize()
{
	m_Menu1 = new MenuPage();
	m_Menu2 = new MenuPage();

	m_LevelLock = LevelJson_.LoadLevelLock();

	Object* background = new Object();
	background->SetTranslation({ -0, 0 });
	background->SetScale({ 1200,900 });
	background->SetDepth(BACKGROUND);
	background->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	background->SetObjectType(ObjectType::Background);
	background->AddComponent(new Sprite("asset/images/Page/LevelSelect.png"));

	CreateMenuPage();

	for(auto& i : m_Menu1->GetButtons())
	{
		Objectmanager_.AddObject(i);
	}
	for (auto& i : m_Menu2->GetButtons())
	{
		Objectmanager_.AddObject(i);
	}
	Objectmanager_.AddObject(background);
}

void LevelSelector::Update(float dt)
{
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
	}

	if (Input::IsKeyTriggered(GLFW_KEY_F10))
	{
		LevelJson_.CreateLevelLockDocument();
	}
}

void LevelSelector::ShutDown()
{
	m_LevelLock.clear();
	UnLoad();
}

void LevelSelector::CreateLevelButton(vector2 pos, vector2 scale, std::string level_text ,std::string numLevel, MenuPage* menu)
{
	Object* button = new Object();
	button->SetTranslation(pos);
	button->SetScale(scale);
	button->SetDepth(HUD_OBJECT);
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::Button);

	auto isLocked = m_LevelLock.find(numLevel)->second;
	button->AddComponent(new UI(level_text, isLocked));

	std::string path = "asset/images/UI/";
	path.append(numLevel);
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


