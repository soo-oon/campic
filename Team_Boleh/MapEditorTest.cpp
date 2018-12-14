#include "MapEditorTest.hpp"
#include "Objectmanager.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "Input.hpp"
#include "Character.hpp"
#include "status.hpp"

enum class ComponentType : int
{
	Sprite = 0,
	Animation = 1,
	Character = 2,
	Collosion = 3
};

void MapEditorTest::Initialize()
{
	GetObjectManager()->GetObjectMapPointer()->clear();
	AddPlayer();
	LoadMap();
	std::cout << "Press keypad 0 to stage 0" << std::endl <<
				"Press keypad 1 to stage 1" << std::endl <<
				"Press keypad 2 to stage 2" << std::endl <<
				"Press keypad 3 to stage 3" << std::endl;
	std::cout << "Press Enter to demonstrate each level" << std::endl;
	if (objects_and_names.size() == 0)
		CreateBackground();

	current_obj_map = GetObjectManager()->GetObjectMapPointer();
}

void MapEditorTest::LoadMap()
{
	GetJson()->GetLoadLevel(STAGE0, &objects_and_names);

	CreateLoadObject();
}

void MapEditorTest::Update(float dt)
{
	//unit size movement.
	if (Input::IsMouseReleased(GLFW_MOUSE_BUTTON_LEFT))
		UnitMovement();

	//Change the stage
	if (Input::IsKeyTriggered(GLFW_KEY_KP_0) || Input::IsKeyTriggered(GLFW_KEY_KP_1))
	{
		int previous_stage_id = selected_stage;

		if (Input::IsKeyTriggered(GLFW_KEY_KP_0))
			selected_stage = (int)stage::Stage0;
		else if (Input::IsKeyTriggered(GLFW_KEY_KP_1))
			selected_stage = (int)stage::Stage1;

		if (previous_stage_id != selected_stage)
		{
			switch (previous_stage_id)
			{
			case (int)stage::Stage0:
				SaveCurrentMap(STAGE0);
				break;
			case (int)stage::Stage1:
				SaveCurrentMap(STAGE1);
				break;
			}
			objects_and_names.clear();
			DrawStage(selected_stage);
		}
	}

	if (Input::IsKeyTriggered(GLFW_KEY_ENTER))
	{
		switch (selected_stage)
		{
		case (int)stage::Stage0:
			SaveCurrentMap(STAGE0);
			break;
		case (int)stage::Stage1:
			SaveCurrentMap(STAGE1);
			break;
		}
	}

	if (Input::IsKeyTriggered(GLFW_KEY_R))
		ChangeLevel("MapEditorTest");

	if (Input::IsKeyTriggered(GLFW_KEY_2))
		ChangeLevel("level2");
	if (Input::IsKeyTriggered(GLFW_KEY_1))
		ChangeLevel("level1");
	if (Input::IsKeyTriggered(GLFW_KEY_4))
		ChangeLevel("Demonstrate");
}

void MapEditorTest::DrawStage(int select)
{
	switch (selected_stage)
	{
	case (int)stage::Stage0:
		DrawStage0();
		break;
	case (int)stage::Stage1:
		DrawStage1();
		break;
	}
}

void MapEditorTest::DrawStage0()
{
	GetJson()->GetLoadLevel("Stage0", &objects_and_names);
	GetObjectManager()->GetObjectMapPointer()->clear();
	AddPlayer();
	CreateLoadObject();
}

void MapEditorTest::DrawStage1()
{
	GetJson()->GetLoadLevel("Stage1", &objects_and_names);
	GetObjectManager()->GetObjectMapPointer()->clear();
	AddPlayer();
	CreateLoadObject();
}

void MapEditorTest::SaveCurrentMap(std::string state_name)
{
	GetJson()->SaveOtherLevel(state_name, current_obj_map);
}

void MapEditorTest::CreateBackground()
{
	GetObjectManager()->AddObject("background");
	GetObjectManager()->FindObject("background")->SetScale({ 1280.f,1280.f });
	GetObjectManager()->FindObject("background")->SetTranslation({ 0,0 });
	GetObjectManager()->FindObject("background")->SetDepth(0.5);
	GetObjectManager()->FindObject("background")->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	GetObjectManager()->FindObject("background")->AddComponent(new Sprite());
	GetObjectManager()->FindObject("background")->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/background.png");
	GetObjectManager()->FindObject("background")->texture_path = "asset/images/background.png";
}

void MapEditorTest::CreateLoadObject()
{
	for (std::map<std::string, Object>::iterator itr = objects_and_names.begin();
		itr != objects_and_names.end(); ++itr)
	{
		std::string object_name = itr->first;

		if (object_name == "Player")
			continue;
		if (object_name == "Sword")
			continue;

		GetObjectManager()->AddObject(object_name);
		GetObjectManager()->FindObject(object_name)->SetScale(itr->second.GetTransform().GetScale());
		GetObjectManager()->FindObject(object_name)->SetTranslation(itr->second.GetTransform().GetTranslation());
		GetObjectManager()->FindObject(object_name)->SetRotation(itr->second.GetTransform().GetRotation());
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
			break;
		case 2:
			GetObjectManager()->FindObject(object_name)->AddComponent(new Character(ObjectType::opponent));
			GetObjectManager()->FindObject(object_name)->AddComponent((new Status(5, 1, 1.f)));
			break;
		case 3:

			break;
		}

		GetObjectManager()->FindObject(itr->first)->texture_path = itr->second.texture_path;
		GetObjectManager()->FindObject(itr->first)->object_id = itr->second.object_id;
	}

}

void MapEditorTest::UnitMovement()
{
	for (auto itr = current_obj_map->begin(); itr != current_obj_map->end(); itr++)
	{
		if (itr->first == "Player")
			continue;
		if (itr->first == "Sword")
			continue;

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