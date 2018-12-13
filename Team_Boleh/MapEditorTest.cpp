#include "MapEditorTest.hpp"
#include "Objectmanager.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "Input.hpp"
#include "Character.hpp"

void MapEditorTest::Initialize()
{
	LoadMap();
	std::cout << "Press 7 to create wall\n"
		<< "      8           road\n"
		<< "      9           heart\n";

	std::string name = "displaybox";
	GetObjectManager()->AddObject(name);
	GetObjectManager()->FindObject(name)->SetScale(vector2(100.f, 100.f));
	GetObjectManager()->FindObject(name)->SetTranslation(vector2(0.f, 0.f));
	GetObjectManager()->FindObject(name)->SetMesh(mesh::CreateLineBox(1, { 255, 255, 255, 255 }));


	if (objects_and_names.size() == 0)
	{
		GetObjectManager()->AddObject("background");
		GetObjectManager()->FindObject("background")->SetScale({ 1280.f,1280.f });
		GetObjectManager()->FindObject("background")->SetTranslation({ 0,0 });
		GetObjectManager()->FindObject("background")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		GetObjectManager()->FindObject("background")->AddComponent(new Sprite());
		GetObjectManager()->FindObject("background")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/background.png");
		GetObjectManager()->FindObject("background")->texture_path = "asset/images/background.png";
		object_count = 1;
	}
	obj_map = GetObjectManager()->GetObjectMapPointer();
}

void MapEditorTest::LoadMap()
{
	GetJson()->GetLoadLevel("MapEditorTest", &objects_and_names);
	for (std::map<std::string, Object>::iterator itr = objects_and_names.begin();
		itr != objects_and_names.end(); ++itr)
	{
		std::string object_name = itr->first;

		if (object_name == "Player")
			continue;
		if (object_name == "Sword")
			continue;
		if (object_name == "displaybox")
			continue;

		GetObjectManager()->AddObject(object_name);
		GetObjectManager()->FindObject(object_name)->SetScale(itr->second.GetTransform().GetScale());
		GetObjectManager()->FindObject(object_name)->SetTranslation(itr->second.GetTransform().GetTranslation());
		GetObjectManager()->FindObject(object_name)->SetRotation(*itr->second.GetTransform().GetRotation());
		GetObjectManager()->FindObject(object_name)->SetDepth(itr->second.GetTransform().GetDepth());
		GetObjectManager()->FindObject(object_name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));

		GetObjectManager()->FindObject(object_name)->AddComponent(new Sprite());
		GetObjectManager()->FindObject(object_name)->GetComponentByTemplate<Sprite>()->Texture_Load(itr->second.texture_path);

		GetObjectManager()->FindObject(object_name)->texture_path = itr->second.texture_path;
		GetObjectManager()->FindObject(object_name)->object_id = itr->second.object_id;
		object_count = GetObjectManager()->FindObject(object_name)->object_id;
	}
}

void MapEditorTest::Update(float dt)
{
	for (auto itr = obj_map->begin(); itr != obj_map->end(); itr++)
	{

		Object* current_obj = itr->second.get();
		vector2 current_trans = current_obj->GetTransform().GetTranslation();
		vector2 current_size = current_obj->GetTransform().GetScale();
		current_trans.x = static_cast<int>(current_trans.x / 20) * 20;
		current_trans.y = static_cast<int>(current_trans.y / 20) * 20;
		current_size.x = static_cast<int>(current_size.x / 20) * 20;
		current_size.y = static_cast<int>(current_size.y / 20) * 20;
		current_obj->SetTranslation(current_trans);
		current_obj->SetScale(current_size);
	}

	if (Input::IsKeyTriggered(GLFW_KEY_4))
		ChangeLevel("Particle");
	if (Input::IsKeyTriggered(GLFW_KEY_2))
		ChangeLevel("test");
	if (Input::IsKeyTriggered(GLFW_KEY_1))
		ChangeLevel("example");
}

void MapEditorTest::ShutDown()
{

}