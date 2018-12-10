#include "MapEditorTest.hpp"
#include "Objectmanager.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "Input.hpp"
#include "Character.hpp"

void MapEditorTest::Initialize()
{
	Load();

	LoadMap();
	std::cout << "Press 7 to create wall\n"
		<< "      8           road\n"
		<< "      9           heart\n";

	if (objects_and_names.size() == 0)
	{
		GetObjectManager()->AddObject("object0");
		GetObjectManager()->FindObject("object0")->SetScale({ 64.f,64.f });
		GetObjectManager()->FindObject("object0")->SetTranslation({ -100,0 });
		GetObjectManager()->FindObject("object0")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		GetObjectManager()->FindObject("object0")->AddComponent(new Sprite());
		GetObjectManager()->FindObject("object0")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/heart.png");
		GetObjectManager()->FindObject("object0")->texture_path = "asset/images/heart.png";
		selected_object = GetObjectManager()->FindObject("object0").get();
	}
	else
	{
		selected_object_id = objects_and_names.size() - 1;
		object_count = objects_and_names.size();
	}
}

void MapEditorTest::LoadMap()
{
	GetJson()->GetLoadLevel("MapEditorTest", &objects_and_names);
	for (std::map<std::string, Object>::iterator itr = objects_and_names.begin();
		itr != objects_and_names.end(); ++itr)
	{
		std::string object_name = itr->first;
		GetObjectManager()->AddObject(object_name);
		GetObjectManager()->FindObject(object_name)->SetScale(itr->second.GetTransform().GetScale());
		GetObjectManager()->FindObject(object_name)->SetTranslation(itr->second.GetTransform().GetTranslation());
		GetObjectManager()->FindObject(object_name)->SetRotation(*itr->second.GetTransform().GetRotation());
		GetObjectManager()->FindObject(object_name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		GetObjectManager()->FindObject(object_name)->AddComponent(new Sprite());
		GetObjectManager()->FindObject(object_name)->GetComponentByTemplate<Sprite>()->Texture_Load(itr->second.texture_path);
		GetObjectManager()->FindObject(object_name)->texture_path = itr->second.texture_path;
		selected_object = GetObjectManager()->FindObject(object_name).get();
	}
}

void MapEditorTest::Update(float dt)
{
	if (Input::IsKeyAnyTriggered())
	{
		if (Input::IsKeyTriggered(GLFW_KEY_KP_7) || (Input::IsKeyTriggered(GLFW_KEY_KP_8)) ||
			Input::IsKeyTriggered(GLFW_KEY_KP_9))
		{
			std::string name = object_name;
			name.append(std::to_string(object_count));

			std::string texture_path;

			GetObjectManager()->AddObject(name);
			GetObjectManager()->FindObject(name)->SetScale({ 64.f, 64.f });
			GetObjectManager()->FindObject(name)->SetTranslation({ 0,0 });
			GetObjectManager()->FindObject(name)->SetMesh(mesh::CreateBox());
			GetObjectManager()->FindObject(name)->SetDepth(0);
			GetObjectManager()->FindObject(name)->AddComponent(new Sprite());

			if (Input::IsKeyPressed(GLFW_KEY_KP_7))
				texture_path = "asset/images/heart.png";
			if (Input::IsKeyPressed(GLFW_KEY_KP_8))
				texture_path = road;
			if (Input::IsKeyPressed(GLFW_KEY_KP_9))
				texture_path = dr_strange_dot;

			GetObjectManager()->FindObject(name)->GetComponentByTemplate<Sprite>()->Texture_Load(texture_path);
			GetObjectManager()->FindObject(name)->texture_path = texture_path;

			object_count++;
			selected_object_id++;
			selected_object = GetObjectManager()->FindObject(name).get();
		}
	}

	if (Input::IsKeyAnyPressed())
	{
		if (Input::IsKeyPressed(GLFW_KEY_RIGHT) || (Input::IsKeyPressed(GLFW_KEY_LEFT)) ||
			(Input::IsKeyPressed(GLFW_KEY_UP)) || (Input::IsKeyPressed(GLFW_KEY_DOWN)) )
		{
			vector2 current_translation = selected_object->GetTransform().GetTranslation();
			if (Input::IsKeyTriggered(GLFW_KEY_RIGHT))
				current_translation.x += 32.f;
			if (Input::IsKeyTriggered(GLFW_KEY_LEFT))
				current_translation.x-= 32.f;
			if (Input::IsKeyTriggered(GLFW_KEY_UP))
				current_translation.y+= 32.f;
			if (Input::IsKeyTriggered(GLFW_KEY_DOWN))
				current_translation.y-= 32.f;

			selected_object->SetTranslation(current_translation);
		}

		if (Input::IsKeyTriggered(GLFW_KEY_SPACE))
		{
			selected_object_id++;
			if (selected_object_id >= object_count) selected_object_id = 0;
			std::string current_select_name = object_name + std::to_string(selected_object_id);

			selected_object = GetObjectManager()->FindObject(current_select_name).get();

			if (!selected_object)
				std::cout << "there are no such thing idiot" << std::endl;

			std::cout << "object size is " << object_count << std::endl;
			std::cout << " current object id is " << selected_object_id << std::endl;

		}

	}

	//std::cout << Input::GetMousePos(1).x<<", "<<Input::GetMousePos(1).y << std::endl;

	if (Input::IsKeyTriggered(GLFW_KEY_2))
		ChangeLevel("test");
	if (Input::IsKeyTriggered(GLFW_KEY_1))
		ChangeLevel("example");
}

void MapEditorTest::ShutDown()
{

}