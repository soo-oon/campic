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

	//Update level every time engine update.
	void UpdateLevel(StateManager* state_manager);
	//Add new level to json document.
	void AddNewLevel();
	void SaveDocument();
	void LoadLevel();
	void LoadLevelDocument(std::string level_name);


private:
	//Fill the document by object manager
	void UpdateDocument(Objectmanager* objectmanager);
	void AddNewObject(Object* object, std::string name);

private:
	rapidjson::Document LevelDocument;
	rapidjson::Document current_level;
	std::string level_label = "Level";
	int level_count = 1;
	
	std::string file_path = "asset/JsonFiles/";

	std::string current_state_name;
	Objectmanager* current_object_manager = nullptr;
};