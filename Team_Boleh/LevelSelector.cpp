#include "LevelSelector.hpp"
#include "LevelJson.hpp"
#include "UI.hpp"

void LevelSelector::Initialize()
{
	//LoadLevel(current_level);

	m_LevelLock = LevelJson_.LoadLevelLock();

	Object* background = new Object();
	background->SetTranslation({ 0 });
	background->SetScale(Application_.GetScreenSize()); 
	background->SetDepth(0.5f);
	background->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	background->SetObjectType(ObjectType::Background);
	background->AddComponent(new Sprite("asset/images/UI/background.png"));

	Object* level1 = new Object();
	level1->SetTranslation({ -200,-200 });
	level1->SetScale({ 100, 100 });
	level1->SetDepth(-0.1f);
	level1->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	level1->SetObjectType(ObjectType::Button);
	level1->AddComponent(new Sprite("asset/images/UI/UpDownPlatform.png"));
	level1->AddComponent(new UI("Level1"));

	Object* level2 = new Object();
	level2->SetTranslation({ -100,-100 });
	level2->SetScale({ 100, 100 });
	level2->SetDepth(-0.1f);
	level2->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	level2->SetObjectType(ObjectType::Button);
	level2->AddComponent(new Sprite("asset/images/UI/UpDownPlatform.png"));
	level2->AddComponent(new UI("Level2"));

	Object* level3 = new Object();
	level3->SetTranslation({ 0,0 });
	level3->SetScale({ 100, 100 });
	level3->SetDepth(-0.1f);
	level3->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	level3->SetObjectType(ObjectType::Button);
	level3->AddComponent(new Sprite("asset/images/UI/UpDownPlatform.png"));
	level3->AddComponent(new UI("Level3"));

	Object* level4 = new Object();
	level4->SetTranslation({ 100,100 });
	level4->SetScale({ 100, 100 });
	level4->SetDepth(-0.1f);
	level4->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	level4->SetObjectType(ObjectType::Button);
	level4->AddComponent(new Sprite("asset/images/UI/UpDownPlatform.png"));
	level4->AddComponent(new UI("Level4"));

	m_Container.push_back(background);
	m_Container.push_back(level1);
	m_Container.push_back(level2);
	m_Container.push_back(level3);
	m_Container.push_back(level4);

	for (auto& i : m_Container)
	{
		Objectmanager_.AddObject(i);
	}
}

void LevelSelector::Update(float dt)
{
	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		m_SelectLevel = Input::ClickObject();

		if(m_SelectLevel)
		{
			SetLevelIndicator(m_SelectLevel->GetComponentByTemplate<UI>()->GetId());
			ChangeLevel(level_indicator);
		}
	}

	if (Input::IsKeyTriggered(GLFW_KEY_F10))
	{
		LevelJson_.CreateLevelLockDocument();
	}
}

void LevelSelector::ShutDown()
{
	m_Container.clear();
	UnLoad();
}

void LevelSelector::LoadLevelLockJson()
{

}
