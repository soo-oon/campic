#include "LevelSelector.hpp"
#include "UI.hpp"
#include "DepthValue.hpp"

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
	mouse_icon->AddComponent(new Sprite("asset/images/MouseCursor.png"));

	CreateMenuPage();

	for(auto& i : m_Menu1->GetButtons())
	{
		Objectmanager_.AddObject(i);
	}
	for (auto& i : m_Menu2->GetButtons())
	{
		Objectmanager_.AddObject(i);
	}
	Objectmanager_.AddObject(mouse_icon);
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
	float base_y = 50.f;

	for (int i = 1, j = 1; i < 10; ++i, ++j)
	{
		if (i == 6)
		{
			base_y -= 150;
			j = 1;
		}
		CreateLevelButton(vector2(-400.f + (120.f*j), base_y), vector2(100, 100), text + std::to_string(i), text + std::to_string(i), m_Menu1);
		text = "Level";
	}

	base_y = 50.f;
	for (int i = 1, j = 1; i < 10; ++i, ++j)
	{
		if (i == 6)
		{
			base_y -= 150;
			j = 1;
		}
		CreateLevelButton(vector2(-400.f + (120.f*j), base_y), vector2(100, 100), text + std::to_string(i+10), text + std::to_string(i+10), m_Menu2);
		text = "Level";
	}
}


