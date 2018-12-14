/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  MapEditorTest.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jihun Park
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#pragma once
#include "State.hpp"
#include "Objectmanager.hpp"
#include "Object.hpp"
#include "JSON.hpp"

#define STAGE0 "Stage0"
#define STAGE1 "Stage1"

enum class stage : int
{
	Stage0 = 0,
	Stage1 = 1,
	Stage2 = 2,
	Stage3 = 3
};

enum class mode :int
{
	EditorMode = 0,
	DemonstrateMode = 1
};

class MapEditorTest : public State
{
public:
	MapEditorTest() { information_ = State_Information::Game;}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override {}

	void LoadMap();

private:
	std::map<std::string, Object> objects_and_names;//load the object by json
	std::map<std::string, Object>* pt_object_map = &objects_and_names;

	std::map<std::string, std::unique_ptr<Object>>* current_obj_map = nullptr;
	int unit_movement = 20;

	void CreateBackground();
	void CreateLoadObject();

	int selected_stage = 0;
	int selected_mode = 0;

	void DrawStage(int select);
	void DrawStage0();
	void DrawStage1();
	//void DrawStage2();
	//void DrawStage3();

	void UnitMovement();
	void SaveCurrentMap(std::string state_name);
};