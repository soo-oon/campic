#include "JSON.hpp"

#define Level		"level"
#define NAME		"name"
#define TRANSLATION "translation"
#define ROTATION	"rotation"
#define SCALE		"scale"
#define DEPTH		"depth"
#define GRAVITY		"gravity"
#define TEXTURE		"texture"

bool JSON::Initialize()
{
	levels.SetObject();
	if (!levels.IsObject())
		return false;
	return true;
}

void JSON::Update(float dt)
{

}

void JSON::Quit()
{
	SaveDocument();
	for (std::map< std::string, std::unique_ptr < rapidjson::Document>>::iterator
		it = LevelDocuments.begin(); it != LevelDocuments.end(); it++)
		delete(it->second.get());
}

void JSON::UpdateLevel(StateManager* state_manager)
{
	std::string name;
	State* currentstat = state_manager->GetCurrentState();
	Objectmanager* currentobjectM = currentstat->GetObjectManager();

	for (std::map <std::string, std::unique_ptr<State>>::iterator
		it = state_manager->GetStateMap().begin(); it != state_manager->GetStateMap().end(); it++)
	{
		if (currentstat == it->second.get())
			name = it->first;
	}

	for (std::map< std::string, std::unique_ptr <rapidjson::Document>>::iterator
		it = LevelDocuments.begin(); it != LevelDocuments.end(); it++)
	{
		if (it->first == name)
		{
			UpdateDocument(currentobjectM, it->second.get());
			return;
		}
	}
	AddNewLevel(currentstat, name);
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
		AddNewLevel(currentstate, name);

		currentObjectM = it->second.get()->GetObjectManager();
		for (std::map<std::string, std::unique_ptr<rapidjson::Document>>::iterator
			it2 = LevelDocuments.begin(); it2 != LevelDocuments.end(); it2++)
		{
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
	for (std::map<std::string, std::unique_ptr<Object>>::iterator
		it = objectmanager->GetObjectMap().begin(); it != objectmanager->GetObjectMap().end(); ++it)
	{
		if (!(document->HasMember(it->first.c_str())))
			AddNewObject(it->second.get(), it->first, document);
		else
			UpdateObject(it->second.get(), it->first, document);
	}
}

void JSON::AddNewObject(Object* object, std::string name, rapidjson::Document* document)
{
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

	//Add Datas to objectdata
	newObjectData.AddMember(NAME, newObjectName, allocator);
	newObjectData.AddMember(TRANSLATION, newObjectTranslation, allocator);
	newObjectData.AddMember(ROTATION, newObjectRotation, allocator);
	newObjectData.AddMember(SCALE, newObjectScale, allocator);
	newObjectData.AddMember(DEPTH, newObjectDepth, allocator);
	newObjectData.AddMember(GRAVITY, newObjectGravity, allocator);
	newObjectData.AddMember(TEXTURE, newObjectTexture, allocator);

	rapidjson::Value nameofobject(name.c_str(), allocator);

	//Add objectdata to document
	document->AddMember(nameofobject, newObjectData, allocator);
}
void JSON::UpdateObject(Object* object, std::string name, rapidjson::Document* document)
{
	rapidjson::Value& a_type_data = (*document)[name.c_str()][TRANSLATION];

	a_type_data[0].SetFloat(object->GetTransform().GetTranslation().x);
	a_type_data[1].SetFloat(object->GetTransform().GetTranslation().y);

	rapidjson::Value& o_type_data = (*document)[name.c_str()][ROTATION];
	o_type_data = (*document)[name.c_str()][ROTATION];
	o_type_data.SetFloat(*(object->GetTransform().GetRotation()));

	(*document)[name.c_str()][SCALE][0].SetFloat(object->GetTransform().GetScale().x);
	(*document)[name.c_str()][SCALE][1].SetFloat(object->GetTransform().GetScale().y);

	(*document)[name.c_str()][DEPTH].SetFloat(object->GetTransform().GetDepth());

	(*document)[name.c_str()][GRAVITY].SetFloat(object->GetGravity());
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
//
//std::vector<Object> JSON::GetLoadLevel(std::string state_name, std::vector<Object*> state_object)
//{
//	rapidjson::Document* levels_document = GetDocumentofLevel(state_name);
//
//
//
//	return std::vector<Object>();
//}