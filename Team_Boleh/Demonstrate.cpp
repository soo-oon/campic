#include "Demonstrate.hpp"
#include "JSON.hpp"
#include "Input.hpp"

#define STAGE0 "Stage0"
#define STAGE1 "Stage1"

void Demonstrate::Initialize()
{
	GetJson()->GetLoadLevel(STAGE0, &stage0);
	GetJson()->GetLoadLevel(STAGE1, &stage1);
	CreateLoadObject(selected_level);
}

void Demonstrate::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_SPACE))
	{
		if (selected_level == 1)
		{
			selected_level = 2;
			MakeItVisible(selected_level, false);
			MakeItVisible(selected_level, true);
		}

		else if (selected_level == 2)
		{
			selected_level = 1;
			MakeItVisible(selected_level, false);
			MakeItVisible(selected_level, true);
		}
	}

	if (Input::IsKeyTriggered(GLFW_KEY_4))
		ChangeLevel("MapEditorTest");

}

void Demonstrate::ShutDown()
{
}

void Demonstrate::MakeItVisible(int stage_id, bool visible_yes)
{

}

void Demonstrate::CreateLoadObject(int stage_id)
{
	for (std::map<std::string, Object>::iterator itr = stage1.begin();
		itr != stage1.end(); ++itr)
	{
		std::string object_name = itr->first;

		if (object_name == "Player")
			continue;
		if (object_name == "Sword")
			continue;

		GetObjectManager()->AddObject(object_name);
		GetObjectManager()->FindObject(object_name)->GetMesh().Invisible();
		GetObjectManager()->FindObject(object_name)->SetScale(itr->second.GetTransform().GetScale());
		GetObjectManager()->FindObject(object_name)->SetTranslation(itr->second.GetTransform().GetTranslation());
		GetObjectManager()->FindObject(object_name)->SetRotation(*itr->second.GetTransform().GetRotation());
		GetObjectManager()->FindObject(object_name)->SetDepth(itr->second.GetTransform().GetDepth());
		GetObjectManager()->FindObject(object_name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));

		GetObjectManager()->FindObject(object_name)->AddComponent(new Sprite());
		GetObjectManager()->FindObject(object_name)->GetComponentByTemplate<Sprite>()->Texture_Load(itr->second.texture_path);

		GetObjectManager()->FindObject(object_name)->texture_path = itr->second.texture_path;
		GetObjectManager()->FindObject(object_name)->object_id = itr->second.object_id;
	}

	for (std::map<std::string, Object>::iterator itr = stage0.begin();
		itr != stage0.end(); ++itr)
	{
		std::string object_name = itr->first;

		if (object_name == "Player")
			continue;
		if (object_name == "Sword")
			continue;

		bool same = false;
		for (std::map<std::string, Object>::iterator itr1 = stage1.begin();
			itr1 != stage1.end(); ++itr1)
		{
			if (itr1->first == object_name)
				same = true;
		}

		if(!same)
			GetObjectManager()->AddObject(object_name);
		GetObjectManager()->FindObject(object_name)->GetMesh().Visible();
		GetObjectManager()->FindObject(object_name)->SetScale(itr->second.GetTransform().GetScale());
		GetObjectManager()->FindObject(object_name)->SetTranslation(itr->second.GetTransform().GetTranslation());
		GetObjectManager()->FindObject(object_name)->SetRotation(*itr->second.GetTransform().GetRotation());
		GetObjectManager()->FindObject(object_name)->SetDepth(itr->second.GetTransform().GetDepth());
		GetObjectManager()->FindObject(object_name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));

		GetObjectManager()->FindObject(object_name)->AddComponent(new Sprite());
		GetObjectManager()->FindObject(object_name)->GetComponentByTemplate<Sprite>()->Texture_Load(itr->second.texture_path);

		GetObjectManager()->FindObject(object_name)->texture_path = itr->second.texture_path;
		GetObjectManager()->FindObject(object_name)->object_id = itr->second.object_id;
	}

}
