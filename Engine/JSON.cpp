/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: JSON.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Ji Hun Park
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "JSON.hpp"
#include "Character.hpp"
#include <fstream>
#include <iostream>

#define Level		"level"
#define NAME		"name"
#define TRANSLATION "translation"
#define ROTATION	"rotation"
#define SCALE		"scale"
#define DEPTH		"depth"
#define GRAVITY		"gravity"
#define TEXTURE		"texture"
#define ID			"id"
#define Sprite_		"sprite"
#define Animation_	"animation"
#define Character_	"character"
#define Collision_	"collision"

enum class ComponentType :int
{
	Sprite = 0,
	Animation = 1,
	Character = 2,
	Collision = 3
};


bool JSON::Initialize()
{
	levels.SetObject();
	if (!levels.IsObject())
		return false;
	LoadLevelDocument();
	return true;
}

void JSON::Update(float dt) { }

void JSON::Quit()
{
	//SaveAtEnd();
	SaveDocument();
	saved_state_manager = nullptr;
	for (std::map< std::string, std::unique_ptr < rapidjson::Document>>::iterator
		it = LevelDocuments.begin(); it != LevelDocuments.end(); it++)
		delete(it->second.get());
}


void JSON::UpdateLevel(StateManager* state_manager) //Engine
{
	if (saved_state_manager)
		return;

	saved_state_manager = state_manager;
}

void JSON::UpdateState(StateManager* state_manager) //State
{
	//if (saved_state_manager)
		//return;

	levels.SetObject();
	LoadLevelDocument();
	level_objects.SetObject();

	saved_state_manager = state_manager;
	currentstate = saved_state_manager->GetCurrentState();

	for (std::map<std::string, std::unique_ptr<State>>::iterator
		it = saved_state_manager->GetStateMap().begin();
		it != saved_state_manager->GetStateMap().end(); it++)
	{
		if (currentstate == it->second.get())
			currentstate_name = it->first;
	}
}

void JSON::SaveAtEnd() //Engine
{
	//SaveAtEnd(saved_state_manager);
	SaveAtEachDocument();
}

void JSON::SaveAtEachDocument() //State
{
	if (!levels.HasMember(currentstate_name.c_str()))
		UpdateLevelToDocument(currentstate_name);

	UpdateDocument(currentstate->GetObjectManager().get(), &level_objects);
	SaveADocument("levels", &levels);
	SaveADocument(currentstate_name, &level_objects);
}

void JSON::SaveAtEnd(StateManager* state_manager) //Engine
{
	std::string name;
	State* currentstate;
	Objectmanager* currentObjectM;

	for (std::map<std::string, std::unique_ptr<State>>::iterator
		it = state_manager->GetStateMap().begin(); it != state_manager->GetStateMap().end(); it++)
	{
		name = it->first;
		currentstate = it->second.get();

		currentObjectM = it->second.get()->GetObjectManager().get();
		if (!currentObjectM) //if currentObejctmanager is empt, it means you didn't turn that level.
			continue;

		AddNewLevel(currentstate, name);
		for (std::map<std::string, std::unique_ptr<rapidjson::Document>>::iterator
			it2 = LevelDocuments.begin(); it2 != LevelDocuments.end(); it2++)
		{
			if(it2->first == name)
			UpdateDocument(currentObjectM, it2->second.get());
		}
	}
}

void JSON::UpdateLevelToDocument(std::string statename)
{
	rapidjson::Value new_level_info(statename.c_str(), levels.GetAllocator());
	rapidjson::Value new_level_name(rapidjson::kObjectType);
	new_level_name.SetString(statename.c_str(),levels.GetAllocator());
	levels.AddMember(new_level_name, new_level_info, levels.GetAllocator());

}

void JSON::AddNewLevel(State* current_state, std::string name)
{
	LevelDocuments.insert(std::make_pair(name,
		new rapidjson::Document(rapidjson::kObjectType)));

	//Level data
	rapidjson::Value newLevel(rapidjson::kObjectType);
	rapidjson::Value newLevelname(name.c_str(), levels.GetAllocator());
	//add to level? member
	newLevel.AddMember(Level, newLevelname, levels.GetAllocator());

	std::string Levelcount = level_name; //temporary levelcountname
	Levelcount.append(std::to_string(level_count));
	//Add to document.
	rapidjson::Value countofLevel(Levelcount.c_str(), levels.GetAllocator());
	levels.AddMember(countofLevel, newLevel, levels.GetAllocator());
	level_count++;
}

void JSON::UpdateDocument(Objectmanager* objectmanager, rapidjson::Document* document)
{
	for (std::map<std::string, std::unique_ptr<Object>>::iterator
		it = objectmanager->GetObjectMap().begin(); it != objectmanager->GetObjectMap().end(); ++it)
	{
		if (!(document->HasMember(it->first.c_str())))
			AddNewObject(it->second.get(), it->first, document);
		//else
		//	UpdateObject(it->second.get(), it->first, document);
	}
}

void JSON::AddNewObject(Object* object, std::string name, rapidjson::Document* document)
{
	if (!object->GetMesh().IsVisible())
		return;
	rapidjson::Value newObjectData(rapidjson::kObjectType);
	rapidjson::Document::AllocatorType& allocator = document->GetAllocator();

	//Add Data of object///////////////////////////////////////
	rapidjson::Value newObjectName(name.c_str(), allocator);

	rapidjson::Value newObjectTranslation(rapidjson::kArrayType);
	newObjectTranslation.PushBack(object->GetTransform().GetTranslation().x, allocator);
	newObjectTranslation.PushBack(object->GetTransform().GetTranslation().y, allocator);

	rapidjson::Value newObjectScale(rapidjson::kArrayType);
	newObjectScale.PushBack(object->GetTransform().GetScale().x, allocator);
	newObjectScale.PushBack(object->GetTransform().GetScale().y, allocator);

	rapidjson::Value newObjectRotation(rapidjson::kObjectType);
	newObjectRotation.SetFloat(*(object->GetTransform().GetRotation()));

	rapidjson::Value newObjectDepth(rapidjson::kObjectType);
	newObjectDepth.SetFloat(object->GetTransform().GetDepth());

	rapidjson::Value newObjectGravity(rapidjson::kObjectType);
	newObjectGravity.SetFloat(object->GetGravity());

	rapidjson::Value newObjectTexture(object->texture_path.c_str(), allocator);

	rapidjson::Value newObjectID(rapidjson::kObjectType);
	newObjectID.SetInt(object->object_id);
	 
	////
	rapidjson::Value newObjectSprite(rapidjson::kObjectType);
	if (object->GetComponentByTemplate<Sprite>())
		newObjectSprite.SetInt(1);
	else
		newObjectSprite.SetInt(0);

	rapidjson::Value newObjectAnimation(rapidjson::kObjectType);
	if (object->GetComponentByTemplate<Animation>())
		newObjectAnimation.SetInt(1);
	else
		newObjectAnimation.SetInt(0);

	rapidjson::Value newObjectCharacter(rapidjson::kObjectType);
	if (object->GetComponentByTemplate<Character>())
		newObjectCharacter.SetInt(1);
	else
		newObjectCharacter.SetInt(0);

	rapidjson::Value newObjectCollision(rapidjson::kObjectType);
	if (object->GetComponentByTemplate<Collision>())
		newObjectCollision.SetInt(1);
	else
		newObjectCollision.SetInt(0);

	newObjectData.AddMember(NAME, newObjectName, allocator);
	newObjectData.AddMember(TRANSLATION, newObjectTranslation, allocator);
	newObjectData.AddMember(ROTATION, newObjectRotation, allocator);
	newObjectData.AddMember(SCALE, newObjectScale, allocator);
	newObjectData.AddMember(DEPTH, newObjectDepth, allocator);
	newObjectData.AddMember(GRAVITY, newObjectGravity, allocator);
	newObjectData.AddMember(TEXTURE, newObjectTexture, allocator);
	newObjectData.AddMember(ID, newObjectID, allocator);

	newObjectData.AddMember(Sprite_, newObjectSprite, allocator);
	newObjectData.AddMember(Animation_, newObjectAnimation, allocator);
	newObjectData.AddMember(Character_, newObjectCharacter, allocator);
	newObjectData.AddMember(Collision_, newObjectCollision, allocator);


	rapidjson::Value nameofobject(name.c_str(), allocator);

	//Add objectdata to document
	document->AddMember(nameofobject, newObjectData, allocator);
}


void JSON::SaveDocument()
{
	//store objects
	for (std::map<std::string, std::unique_ptr<rapidjson::Document>>
		::iterator it = LevelDocuments.begin(); it != LevelDocuments.end(); ++it)
	{
		FILE* fp;
		std::string filename = file_path;
		filename.append(it->first);
		filename.append(".json");
		fopen_s(&fp, filename.c_str(), "wb");

		char writeBuffer[65535];
		rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
		rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
		it->second.get()->Accept(writer);
		fclose(fp);
	}

	//store levels
	FILE* fp;
	std::string filename = file_path;
	filename.append("levels.json");
	fopen_s(&fp, filename.c_str(), "wb");
	char writeBuffer[65535];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
	levels.Accept(writer);
	fclose(fp);
}

void JSON::LoadDocument()
{
	//load levels
	LoadLevelDocument();

	for (rapidjson::Value::ConstMemberIterator itr = levels.MemberBegin();
		itr != levels.MemberEnd(); ++itr)
	{
		//Add new document
		rapidjson::Document *newLevelObjectData = new rapidjson::Document(rapidjson::kObjectType);

		std::string file_name = file_path;
		file_name.append(itr->name.GetString());
		file_name.append(".json");
		FILE* fp;
		fopen_s(&fp, file_name.c_str(), "rb");
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		newLevelObjectData->ParseStream(is);
		fclose(fp);

		LevelDocuments.insert(std::make_pair(itr->name.GetString(), newLevelObjectData));
	}
}

void JSON::LoadLevelDocument()
{
	FILE* fp;
	fopen_s(&fp, "asset/JsonFiles/levels.json", "rb");
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	levels.ParseStream(is);
	fclose(fp);
}

rapidjson::Document* JSON::GetDocumentofLevel(std::string level_name)
{
	for (std::map<std::string, std::unique_ptr<rapidjson::Document>>
		::iterator it = LevelDocuments.begin(); it != LevelDocuments.end(); ++it)
	{
		if (it->first == level_name)
			return it->second.get();
	}

	return nullptr;
}

void JSON::GetLoadLevel(std::string state_name, std::map<std::string, Object>* state_object)
{
	rapidjson::Document load_document;
	FILE* fp;
	std::string file_name = file_path;
	file_name.append(state_name);
	file_name.append(".json");
	fopen_s(&fp, file_name.c_str(), "rb");
	char readBuffer[65535];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	load_document.ParseStream(is);
	fclose(fp);

	for (rapidjson::Value::ConstMemberIterator itr = load_document.MemberBegin();
		itr != load_document.MemberEnd(); itr++)
	{
		std::string load_object_name = itr->name.GetString();
		vector2 load_scale = { itr->value["scale"][0].GetFloat(), itr->value["scale"][1].GetFloat() };
		vector2 load_translation = { itr->value["translation"][0].GetFloat(), itr->value["translation"][1].GetFloat() };
		float load_rotation = itr->value["rotation"].GetFloat();
		float load_depth = itr->value["depth"].GetFloat();

		//int sprite_ = itr->value["sprite"].GetInt();

		Object new_object;
		new_object.SetScale(load_scale);
		new_object.SetTranslation(load_translation);
		new_object.SetRotation(load_rotation);
		new_object.SetDepth(load_depth);
		new_object.texture_path = itr->value["texture"].GetString();
		new_object.object_id = itr->value["id"].GetInt();

		if (itr->value["sprite"].GetInt())
			new_object.component_type_id = 0;
		else if (itr->value["animation"].GetInt())
			new_object.component_type_id = 1;
		else if (itr->value["character"].GetInt())
			new_object.component_type_id = 2;
		else if (itr->value["collision"].GetInt())
			new_object.component_type_id = 3;

		state_object->insert(std::pair<std::string, Object>(load_object_name, new_object));
	}
}

void JSON::SaveADocument(std::string docu_name, rapidjson::Document* docu)
{
	FILE* fp;
	std::string filename = file_path + docu_name + ".json";
	fopen_s(&fp, filename.c_str(), "wb");

	char writeBuffer[65535];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
	docu->Accept(writer);
	fclose(fp);
}

void JSON::SaveOtherLevel
(std::string state_name, std::map<std::string, std::unique_ptr<Object>>*state_object)
{
	if (!levels.HasMember(state_name.c_str()))
		UpdateLevelToDocument(state_name);

	rapidjson::Document* new_document = new rapidjson::Document;
	new_document->SetObject();
	for (auto itr = state_object->begin(); itr != state_object->end(); itr++)
		AddNewObject(itr->second.get(), itr->first, new_document);

	SaveADocument(state_name, new_document);
	delete new_document;
}