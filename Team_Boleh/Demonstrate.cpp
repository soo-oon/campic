#include "Demonstrate.hpp"
#include "JSON.hpp"
#include "Input.hpp"
#include "Character.hpp"
#include "Status.hpp"

#define STAGE0 "Stage0"
#define STAGE1 "Stage1"

void Demonstrate::Initialize()
{
	GetJson()->GetLoadLevel(STAGE0, &stage0);
	CreateLoadObject(selected_level);
}

void Demonstrate::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_ENTER))
	{
		if (selected_level == 0)
			selected_level = 1;

		else if (selected_level == 1)
			selected_level = 0;
		DrawStage(selected_level);
	}

	player_info = *(GetObjectManager()->FindObject("Player").get());
	sword_info = *(GetObjectManager()->FindObject("Sword").get());

	if (Input::IsKeyTriggered(GLFW_KEY_4))
		ChangeLevel("MapEditorTest");

}

void Demonstrate::ShutDown()
{

}

void Demonstrate::DrawStage(int selected_stage_id)
{
	switch (selected_stage_id)
	{
	case 0:
		DrawStage0();
		break;
	case 1:
		DrawStage1();
		break;
	}
	GetObjectManager()->FindObject("Player")->SetTranslation(player_info.GetTransform().GetTranslation());
	GetObjectManager()->FindObject("Player")->SetRotation(*player_info.GetTransform().GetRotation());
	GetObjectManager()->FindObject("Sword")->SetTranslation(sword_info.GetTransform().GetTranslation());
	GetObjectManager()->FindObject("Sword")->SetRotation(*sword_info.GetTransform().GetRotation());
}

void Demonstrate::DrawStage0()
{
	GetJson()->GetLoadLevel("Stage0", &stage0);
	GetObjectManager()->GetObjectMapPointer()->clear();
	AddPlayer();
	CreateLoadObject(selected_level);
}

void Demonstrate::DrawStage1()
{
	GetJson()->GetLoadLevel("Stage1", &stage1);
	GetObjectManager()->GetObjectMapPointer()->clear();
	AddPlayer();
	CreateLoadObject(selected_level);
}
void Demonstrate::CreateLoadObject(int stage_id)
{
	std::map<std::string, Object>* temp = nullptr;

	if (stage_id == 0)
		temp = &stage0;
	else if(stage_id == 1)
		temp = &stage1;

	for (std::map<std::string, Object>::iterator itr = temp->begin();
		itr != temp->end(); ++itr)
	{
		std::string object_name = itr->first;

		if (object_name == "Player")
			continue;
		if (object_name == "Sword")
			continue;

		GetObjectManager()->AddObject(object_name);
		GetObjectManager()->FindObject(object_name)->SetScale(itr->second.GetTransform().GetScale());
		GetObjectManager()->FindObject(object_name)->SetTranslation(itr->second.GetTransform().GetTranslation());
		GetObjectManager()->FindObject(object_name)->SetRotation(*itr->second.GetTransform().GetRotation());
		GetObjectManager()->FindObject(object_name)->SetDepth(itr->second.GetTransform().GetDepth());
		GetObjectManager()->FindObject(object_name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		
		switch (itr->second.component_type_id)
		{
		case 0:
			GetObjectManager()->FindObject(object_name)->AddComponent(new Sprite());
			GetObjectManager()->FindObject(object_name)->GetComponentByTemplate<Sprite>()->Texture_Load(itr->second.texture_path);
			break;
		case 1:
			GetObjectManager()->FindObject(object_name)->AddComponent(new Animation(itr->second.texture_path, "slime", 6, 0.25));
			GetObjectManager()->FindObject(object_name)->AddComponent(new RigidBody());
			GetObjectManager()->FindObject(object_name)->AddComponent(new Collision(box_, {}, { itr->second.GetTransform().GetScale() }));
			GetObjectManager()->FindObject(object_name)->AddComponent(new Character(ObjectType::opponent));
			GetObjectManager()->FindObject(object_name)->AddComponent(new Status(5, 1, 1.f));
			break;
		case 2:
			GetObjectManager()->FindObject(object_name)->AddComponent(new Character(ObjectType::opponent));
			GetObjectManager()->FindObject(object_name)->AddComponent((new Status(5, 1, 1.f)));
			break;
		case 3:

			break;
		}

		GetObjectManager()->FindObject(object_name)->texture_path = itr->second.texture_path;
		GetObjectManager()->FindObject(object_name)->object_id = itr->second.object_id;
	}
}
