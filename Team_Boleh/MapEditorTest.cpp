#include "MapEditorTest.hpp"
#include "Objectmanager.hpp"
#include <iostream>
#include "Sprite.hpp"
#include "Input.hpp"
#include "Character.hpp"

void MapEditorTest::Initialize()
{
	GetObjectManager()->GetObjectMapPointer()->clear();
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

	if (Input::IsKeyTriggered(GLFW_KEY_4))
		ChangeLevel("MapEditorTest");

	if (Input::IsKeyTriggered(GLFW_KEY_4))
		ChangeLevel("Particle");
	if (Input::IsKeyTriggered(GLFW_KEY_2))
		ChangeLevel("test");
	if (Input::IsKeyTriggered(GLFW_KEY_1))
		ChangeLevel("example");
	if (Input::IsKeyTriggered(GLFW_KEY_5))
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
	CreateLoadObject();
}

void MapEditorTest::DrawStage1()
{
	GetJson()->GetLoadLevel("Stage1", &objects_and_names);
	GetObjectManager()->GetObjectMapPointer()->clear();
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

		GetObjectManager()->AddObject(itr->first);
		GetObjectManager()->FindObject(itr->first)->SetScale(itr->second.GetTransform().GetScale());
		GetObjectManager()->FindObject(itr->first)->SetTranslation(itr->second.GetTransform().GetTranslation());
		GetObjectManager()->FindObject(itr->first)->SetRotation(*itr->second.GetTransform().GetRotation());
		GetObjectManager()->FindObject(itr->first)->SetDepth(itr->second.GetTransform().GetDepth());
		GetObjectManager()->FindObject(itr->first)->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));

		GetObjectManager()->FindObject(itr->first)->AddComponent(new Sprite());
		GetObjectManager()->FindObject(itr->first)->GetComponentByTemplate<Sprite>()->Texture_Load(itr->second.texture_path);

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