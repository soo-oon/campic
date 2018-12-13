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

	//std::string name = "displaybox";
	//GetObjectManager()->AddObject(name);
	//GetObjectManager()->FindObject(name)->SetScale(vector2(100.f, 100.f));
	//GetObjectManager()->FindObject(name)->SetTranslation(vector2(0.f, 0.f));
	//GetObjectManager()->FindObject(name)->SetMesh(mesh::CreateLineBox(1, { 0, 0, 255, 255 }));


	if (objects_and_names.size() == 0)
	{
		GetObjectManager()->AddObject("background");
		GetObjectManager()->FindObject("background")->SetScale({ 1280.f,1280.f });
		GetObjectManager()->FindObject("background")->SetTranslation({ 0,0 });
		GetObjectManager()->FindObject("background")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		GetObjectManager()->FindObject("background")->AddComponent(new Sprite());
		GetObjectManager()->FindObject("background")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/background.png");
		GetObjectManager()->FindObject("background")->texture_path = "asset/images/background.png";
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
	}
}

void MapEditorTest::Update(float dt)
{
	//unit size movement.
	if (Input::IsMouseReleased(GLFW_MOUSE_BUTTON_LEFT))
	{
		for (auto itr = obj_map->begin(); itr != obj_map->end(); itr++)
		{
			Object* current_obj = itr->second.get();
			int trans_x = (int)current_obj->GetTransform().GetTranslation().x;
			int trans_y = (int)current_obj->GetTransform().GetTranslation().y;
			int size_x = (int)current_obj->GetTransform().GetScale().x;
			int size_y = (int)current_obj->GetTransform().GetScale().y;

			trans_x = trans_x / unit_movement * unit_movement;
			trans_y = trans_y / unit_movement * unit_movement;
			size_x = size_x / unit_movement * unit_movement;
			size_y = size_y / unit_movement * unit_movement;
 			current_obj->SetTranslation(vector2(static_cast<float>(trans_x), static_cast<float>(trans_y)));
			current_obj->SetScale(vector2(static_cast<float>(size_x), static_cast<float>(size_y)));
		}
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