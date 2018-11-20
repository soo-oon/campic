#include "MapEditorTest.hpp"
#include "Objectmanager.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "Input.hpp"
#include "Character.hpp"

void MapEditorTest::Initialize()
{
	Load();

	std::cout << "Press 7 to create wall\n"
		<< "      8           road\n"
		<< "      9           heart\n";

	GetObjectManager()->AddObject("TempObject");
	GetObjectManager()->FindObject("TempObject")->SetScale({ 64.f,64.f });
	GetObjectManager()->FindObject("TempObject")->SetTranslation({ -100,0 });
	GetObjectManager()->FindObject("TempObject")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("TempObject")->AddComponent(new Sprite());
	GetObjectManager()->FindObject("TempObject")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/heart.png");
	GetObjectManager()->FindObject("TempObject")->texture_path = "asset/images/heart.png";

	selected_object = GetObjectManager()->FindObject("TempObject").get();
}

void MapEditorTest::LoadMap()
{
	//mapeditor_json.GetLoadLevel("MapEditorTest", objects);
}

void MapEditorTest::Update(float dt)
{
	if (Input::IsKeyAnyTriggered())
	{
		if (Input::IsKeyTriggered(GLFW_KEY_KP_7) || (Input::IsKeyTriggered(GLFW_KEY_KP_8)) ||
			Input::IsKeyTriggered(GLFW_KEY_KP_9))
		{
			Object* new_object = new Object;
			std::string name = object_name;
			name.append(std::to_string(object_count));

			std::string texture_path;

			GetObjectManager()->AddObject(name);
			GetObjectManager()->FindObject(name)->SetScale({ 64.f, 64.f });
			GetObjectManager()->FindObject(name)->SetTranslation({ 0,0 });
			GetObjectManager()->FindObject(name)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
			GetObjectManager()->FindObject(name)->SetDepth(0);
			GetObjectManager()->FindObject(name)->AddComponent(new Sprite());

			if (Input::IsKeyPressed(GLFW_KEY_KP_7))
				texture_path = wall_;
			if (Input::IsKeyPressed(GLFW_KEY_KP_8))
				texture_path = road;
			if (Input::IsKeyPressed(GLFW_KEY_KP_9))
				texture_path = dr_strange_dot;

			GetObjectManager()->FindObject(name)->GetComponentByTemplate<Sprite>()->Texture_Load(texture_path);
			GetObjectManager()->FindObject(name)->texture_path = texture_path;

			new_object = GetObjectManager()->FindObject(name).get();
			newObject = new_object;
			objects.push_back(newObject);
			selected_object = newObject;

			object_count++;
		}
	}

	if (Input::IsKeyTriggered(GLFW_KEY_2))
		ChangeLevel("test");
	if (Input::IsKeyTriggered(GLFW_KEY_1))
		ChangeLevel("example");
}

void MapEditorTest::ShutDown()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	UnLoad();
}