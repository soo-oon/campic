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
#include "writer.h"
#include "stringbuffer.h"
#include "filewritestream.h"
#include "filereadstream.h"
#include "Objectmanager.hpp"
#include "prettywriter.h"
#include "StateManager.hpp"
#include "State.hpp"
#include <map>

using namespace rapidjson;

class JSON
{
public:
	bool Initialize();
	void Update(float dt);
	void Quit();

	//Objects
	void ObjectsToDocument(Object* obj);
	void SaveObjectsToJson();
	void LoadObjectFromJson();
	Document LoadObjectDocumentFromJson();

	//Helper class
	Value ComponentAnimation(Object* obj);
	Value ComponentTransform(Object* obj);
	Value ComponentStatus(Object* obj);
	Value ComponentCamera(Object* obj);
	Value ComponentSprite(Object* obj);
	Value ComponentCollision(Object* obj);
	Value ComponentParticle(Object* obj);


	Document& GetObjectDocument() { return ObjectDocument; }

	//void UpdateLevel(StateManager* state_manager);
	//void UpdateState(StateManager* state_manager);
	//void AddNewLevel(State* current_state, std::string name);
	//void UpdateLevelToDocument(std::string statename);
	//void UpdateDocument(Objectmanager* objectmanager, rapidjson::Document* document);
	//void AddNewObject(Object* object, std::string name, rapidjson::Document* document);
	
	//void SaveDocument();
	//void SaveADocument(std::string docu_name, rapidjson::Document* docu);
	//void LoadDocument();
	//void LoadLevelDocument();

	////Please put this function before object manager discarded.
	//void SaveAtEnd(StateManager* state_manager);
	//void SaveAtEnd();
	//void SaveAtEachDocument();

	////for map editor.
	//void GetLoadLevel(std::string state_name, std::map<std::string, Object>* state_object);
	//rapidjson::Document* GetDocumentofLevel(std::string level_name);
	//void SaveOtherLevel(std::string state_name, std::map<std::string, std::unique_ptr<Object>>*state_object);

private:
	Document ObjectDocument;
	StringBuffer ObjectBuffer;

	std::string file_path = "asset/JsonFiles/";

};

extern JSON JSON_;