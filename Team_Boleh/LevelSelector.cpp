#include "LevelSelector.hpp"
#include "UI.hpp"

void LevelSelector::Initialize()
{
	m_LevelLock = LevelJson_.LoadLevelLock();

	std::string text = "Level";

	float base_y = 50.f;

	for(int i = 1,j=1; i <= 10; ++i,++j)
	{
		if(i == 6)
		{
			base_y -= 150;
			j = 1;
		}
		CreateLevelButton(vector2(-350.f+(120.f*j), base_y), vector2(100, 100), text + std::to_string(i), text+std::to_string(i));
		text = "Level";
	}
}

void LevelSelector::Update(float dt)
{
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

void LevelSelector::CreateLevelButton(vector2 pos, vector2 scale, std::string level_text /*,std::string & font*/,std::string level_id)
{
	Object* button = new Object();
	button->SetTranslation(pos);
	button->SetScale(scale);
	button->SetDepth(HUD_OBJECT);
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::Button);

	auto is_lock = m_LevelLock.find(level_id)->second;
	button->AddComponent(new UI(level_text, is_lock));

	if (is_lock)
	{
		button->AddComponent(new Sprite("asset/images/UI/LevelBox.png"));
	}
	button->AddComponent(new Sprite("asset/images/UI/LevelLock.png"));

	Objectmanager_.AddObject(button);
}
