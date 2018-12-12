#include "JSON.hpp"

#define Level		"level"
#define NAME		"name"
#define TRANSLATION "translation"
#define ROTATION	"rotation"
#define SCALE		"scale"
#define DEPTH		"depth"
#define GRAVITY		"gravity"
#define TEXTURE		"texture"
#define ID			"id"

bool JSON::Initialize()
{
	levels.SetObject();
	if (!levels.IsObject())
		return false;
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


void JSON::UpdateLevel(StateManager* state_manager)
{
	if (saved_state_manager)
		return;

	saved_state_manager = state_manager;
}

void JSON::SaveAtEnd()
{
	SaveAtEnd(saved_state_manager);
}


void JSON::SaveAtEnd(StateManager* state_manager)
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
	object_id_count = 1;
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
	newObjectID.SetInt(object_id_count);
	object_id_count++;

	//Add Datas to objectdata
	newObjectData.AddMember(NAME, newObjectName, allocator);
	newObjectData.AddMember(TRANSLATION, newObjectTranslation, allocator);
	newObjectData.AddMember(ROTATION, newObjectRotation, allocator);
	newObjectData.AddMember(SCALE, newObjectScale, allocator);
	newObjectData.AddMember(DEPTH, newObjectDepth, allocator);
	newObjectData.AddMember(GRAVITY, newObjectGravity, allocator);
	newObjectData.AddMember(TEXTURE, newObjectTexture, allocator);
	newObjectData.AddMember(ID, newObjectID, allocator);

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
	FILE* fp;
	fopen_s(&fp, "asset/levels", "rb");
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	levels.ParseStream(is);
	fclose(fp);

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
	fopen_s(&fp, "asset/JsonFiles/MapEditorTest.json", "rb");
	char readBuffer[65535];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	load_document.ParseStream(is);
	fclose(fp);

	for (rapidjson::Value::ConstMemberIterator itr = load_document.MemberBegin();
		itr != load_document.MemberEnd(); ++itr)
	{
		std::string load_object_name = itr->name.GetString();
		vector2 load_scale = { itr->value["scale"][0].GetFloat(), itr->value["scale"][0].GetFloat() };
		vector2 load_translation = { itr->value["translation"][0].GetFloat(), itr->value["translation"][1].GetFloat() };
		float load_rotation = itr->value["rotation"].GetFloat();

		Object new_object;
		new_object.SetScale(load_scale);
		new_object.SetScale(load_scale);
		new_object.SetTranslation(load_translation);
		new_object.SetRotation(load_rotation);
		new_object.texture_path = itr->value["texture"].GetString();
		state_object->insert(std::pair<std::string, Object>(load_object_name, new_object));
	}
}
