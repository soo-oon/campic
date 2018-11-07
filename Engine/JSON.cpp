#include "JSON.hpp"

#define NAME		"name"
#define TRANSLATION "translation"
#define ROTATION	"rotation"
#define SCALE		"scale"
#define DEPTH		"depth"
#define GRAVITY		"gravity"

bool JSON::Initialize()
{
	document.SetObject();
	if (!document.IsObject())
		return false;
	return true;
}

void JSON::UpdateData(Objectmanager* objectmanager)
{
	Object* currentObject = nullptr;
	for (std::map<std::string, std::unique_ptr<Object>>::iterator it = objectmanager->GetObjectMap().begin();
		it != objectmanager->GetObjectMap().end(); ++it)
	{
		SendData(it->second.get(), it->first);
	}

}

void JSON::Quit()
{
	StoreData();
}

void JSON::SendData(Object* object, std::string name)
{
	if (!document.HasMember(name.c_str()))
		AddNewObjectData(object, name);
	else
		ModifyObjectData(object, name);
}

void JSON::AddNewObjectData(Object* object, std::string name)
{
	rapidjson::Value newObjectData(rapidjson::kObjectType);

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

	//Add Datas to objectdata
	newObjectData.AddMember(NAME, newObjectName, allocator);
	newObjectData.AddMember(TRANSLATION,newObjectTranslation, allocator);
	newObjectData.AddMember(ROTATION, newObjectRotation, allocator);
	newObjectData.AddMember(SCALE, newObjectScale, allocator);
	newObjectData.AddMember(DEPTH, newObjectDepth, allocator);
	newObjectData.AddMember(GRAVITY, newObjectGravity, allocator);

	rapidjson::Value nameofobject(name.c_str(), allocator);

	//Add objectdata to document
	document.AddMember(nameofobject, newObjectData,allocator);
}

void JSON::ModifyObjectData(Object* object, std::string name)
{
	rapidjson::Value& a_type_data = document[name.c_str()][TRANSLATION];

	a_type_data[0].SetFloat(object->GetTransform().GetTranslation().x);
	a_type_data[1].SetFloat(object->GetTransform().GetTranslation().y);

	rapidjson::Value& o_type_data = document[name.c_str()][ROTATION];
	o_type_data = document[name.c_str()][ROTATION];
	o_type_data.SetFloat(*(object->GetTransform().GetRotation()));

	document[name.c_str()][SCALE][0].SetFloat(object->GetTransform().GetScale().x);
	document[name.c_str()][SCALE][1].SetFloat(object->GetTransform().GetScale().y);

	document[name.c_str()][DEPTH].SetFloat(object->GetTransform().GetDepth());

	document[name.c_str()][GRAVITY].SetFloat(object->GetGravity());
}

void JSON::LoadData()
{
	FILE* fp;
	fopen_s(&fp, file_name, "wb");
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	document.ParseStream(is);
	fclose(fp);
}

void JSON::StoreData()
{
	FILE *fp;
	fopen_s(&fp, file_name, "wb");

	char writeBuffer[65535];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);

	document.Accept(writer);
	fclose(fp);
}