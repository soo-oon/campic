#include "LevelSelector.hpp"
#include "UI.hpp"

void LevelSelector::Initialize()
{
	//LoadLevel(current_level);

	background = new Object();
	background->SetTranslation({ 0 });
	background->SetScale(Application_.GetScreenSize()); 
	background->SetDepth(0.5f);
	background->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	background->SetObjectType(ObjectType::Background);
	background->AddComponent(new Sprite("asset/images/UI/background.png"));

	level2 = new Object();
	level2->SetTranslation({ -200,0 });
	level2->SetScale({ 522, 150 });
	level2->SetDepth(-0.1f);
	level2->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	level2->SetObjectType(ObjectType::Button);
	level2->AddComponent(new Sprite("asset/images/UI/StartButton.png"));
	level2->AddComponent(new UI("Level3"));
	
	container.push_back(background);
	container.push_back(level2);

	for (auto& i : container)
	{
		Objectmanager_.AddObject(i);
	}
}

void LevelSelector::Update(float dt)
{
	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		select_level = Input::ClickObject();

		if(select_level)
		{
			SetLevelIndicator(select_level->GetComponentByTemplate<UI>()->GetId());
			ChangeLevel("Level3");
		}
	}
}

void LevelSelector::ShutDown()
{
	container.clear();
	UnLoad();
}
