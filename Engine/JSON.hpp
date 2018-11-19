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
	void AddNewLevel(State* current_state, std::string name);
	void UpdateDocument(Objectmanager* objectmanager, rapidjson::Document* document);
	void AddNewObject(Object* object, std::string name, rapidjson::Document* document);
	void UpdateObject(Object* object, std::string name, rapidjson::Document* document);
	void SaveDocument();
	void LoadDocument();

	//if you want to save all data just when game is quit(not update every time)
	//use this function and put it in to Engine->Quit();
	//And erase update function...
	void SaveAtEnd(StateManager* state_manager);
	//not... tested it yet......

	//for map editor.
	std::vector<Object> GetLoadLevel(std::string state_name, std::vector<Object*> state_object);
	rapidjson::Document* GetDocumentofLevel(std::string level_name);

private:
	std::map<std::string, std::unique_ptr<rapidjson::Document>> LevelDocuments;
	rapidjson::Document levels;
	int level_count = 1;
	std::string level_name = "Level";
	std::string file_path = "asset/JsonFiles/";
};