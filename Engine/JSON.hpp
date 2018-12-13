#pragma once
#include "document.h"
#include "filewritestream.h"
#include "filereadstream.h"
#include "Objectmanager.hpp"
#include "prettywriter.h"
#include <map>
#include "StateManager.hpp"
#include "State.hpp"

class JSON : public System
{
public:
	bool Initialize() override;
	void Update(float dt) override;
	void Quit() override;

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