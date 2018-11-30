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
	LoadLevel();
	current_level.SetObject();
	if (!current_level.IsObject())
		return false;
	return true;
}

void JSON::Update(float dt)
{
}

void JSON::Quit()
{

	UpdateDocument(current_object_manager);
	current_object_manager = nullptr;
	SaveDocument();
}


void JSON::UpdateLevel(StateManager* state_manager)
{
	if (current_object_manager)
		return;

	State* currentstat = state_manager->GetCurrentState();
	current_object_manager = currentstat->GetObjectManager();

	//Get the state name.
	for (std::map <std::string, std::unique_ptr<State>>::iterator
		it = state_manager->GetStateMap().begin(); it != state_manager->GetStateMap().end(); it++)
	{
		if (currentstat == it->second.get())
			current_state_name = it->first;
	}

	//if it's new state, add. or do nothing.
	if(!(LevelDocument.HasMember(current_state_name.c_str())))
		AddNewLevel();
}

void JSON::AddNewLevel()
{
	rapidjson::Value newLevel(current_state_name.c_str(),LevelDocument.GetAllocator());
	rapidjson::Value Levelcount((level_label + std::to_string(level_count)).c_str(), LevelDocument.GetAllocator());
	LevelDocument.AddMember(Levelcount, newLevel, LevelDocument.GetAllocator());
}

void JSON::UpdateDocument(Objectmanager* objectmanager)
{
	for (std::map<std::string, std::unique_ptr<Object>>::iterator
		it = objectmanager->GetObjectMap().begin(); it != objectmanager->GetObjectMap().end(); ++it)
	{
		AddNewObject(it->second.get(), it->first);
	}
}

void JSON::AddNewObject(Object* object, std::string name)
{
	rapidjson::Value newObjectData(rapidjson::kObjectType);
	rapidjson::Document::AllocatorType& allocator = current_level.GetAllocator();

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
	current_level.AddMember(nameofobject, newObjectData, allocator);
}


void JSON::SaveDocument()
{
	////store level document
	{
		FILE* fp;
		std::string filename = file_path;
		filename.append("levels.json");
		fopen_s(&fp, filename.c_str(), "wb");
		char writeBuffer[65535];
		rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
		rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
		LevelDocument.Accept(writer);
		fclose(fp);
	}

	//store object document
	{
		FILE* fp;
		std::string filename = file_path;
		filename.append(current_state_name);
		filename.append(".json");
		fopen_s(&fp, filename.c_str(), "wb");
		char writeBuffer[65535];
		rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
		rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
		current_level.Accept(writer);
		fclose(fp);
	}
}

void JSON::LoadLevel()
{
	//load levels
	FILE* fp;
	std::string filename = file_path;
	filename.append("levels.json");
	fopen_s(&fp, filename.c_str(), "rb");
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	LevelDocument.ParseStream(is);
	fclose(fp);
}
void JSON::LoadLevelDocument(std::string level_name)
{
	FILE* fp;
	std::string filename = file_path;
	filename.append(level_name);
	filename.append(".json");
	fopen_s(&fp, filename.c_str(), "rb");
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	current_level.ParseStream(is);
	fclose(fp);
}