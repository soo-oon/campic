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

	level1 = new Object();
	level1->SetTranslation({ -200,200 });
	level1->SetScale({ 522, 150 });
	level1->SetDepth(-0.1f);
	level1->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	level1->SetObjectType(ObjectType::Button);
	level1->AddComponent(new Sprite("asset/images/UI/StartButton.png"));
	level1->AddComponent(new UI("Level1"));

	level2 = new Object();
	level2->SetTranslation({ -200,0 });
	level2->SetScale({ 522, 150 });
	level2->SetDepth(-0.1f);
	level2->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	level2->SetObjectType(ObjectType::Button);
	level2->AddComponent(new Sprite("asset/images/UI/StartButton.png"));
	level2->AddComponent(new UI("Level2"));

	level3 = new Object();
	level3->SetTranslation({ -200,-200 });
	level3->SetScale({ 522, 150 });
	level3->SetDepth(-0.1f);
	level3->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	level3->SetObjectType(ObjectType::Button);
	level3->AddComponent(new Sprite("asset/images/UI/StartButton.png"));
	level3->AddComponent(new UI("Level3"));
	
	container.push_back(background);
	container.push_back(level1);
	container.push_back(level2);
	container.push_back(level3);

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
