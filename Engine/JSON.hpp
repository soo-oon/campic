/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: JSON.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Ji Hun Park
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "document.h"
#include "filewritestream.h"
#include "filereadstream.h"
#include "Objectmanager.hpp"
#include "prettywriter.h"
#include <map>
#include "StateManager.hpp"
#include "State.hpp"

class JSON
{
public:
	bool Initialize();
	void Update(float dt);
	void Quit();

	void UpdateLevel(StateManager* state_manager);
	void UpdateState(StateManager* state_manager);
	void AddNewLevel(State* current_state, std::string name);
	void UpdateLevelToDocument(std::string statename);
	void UpdateDocument(Objectmanager* objectmanager, rapidjson::Document* document);
	void AddNewObject(Object* object, std::string name, rapidjson::Document* document);
	
	void SaveDocument();
	void SaveADocument(std::string docu_name, rapidjson::Document* docu);
	void LoadDocument();
	void LoadLevelDocument();

	//Please put this function before object manager discarded.
	void SaveAtEnd(StateManager* state_manager);
	void SaveAtEnd();
	void SaveAtEachDocument();

	//for map editor.
	void GetLoadLevel(std::string state_name, std::map<std::string, Object>* state_object);
	rapidjson::Document* GetDocumentofLevel(std::string level_name);
	void SaveOtherLevel(std::string state_name, std::map<std::string, std::unique_ptr<Object>>*state_object);

private:
	std::map<std::string, std::unique_ptr<rapidjson::Document>> LevelDocuments;
	rapidjson::Document levels;
	rapidjson::Document level_objects;

	int level_count = 1;
	std::string level_name = "Level";
	std::string file_path = "asset/JsonFiles/";

	Objectmanager* current_object_manager = 0;
	StateManager* saved_state_manager = 0;

	State* currentstate = nullptr;
	std::string currentstate_name;
};

extern JSON JSON_;