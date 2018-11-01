#include "JSON.hpp"

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

	//Add Data of object
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
	newObjectData.AddMember("name", newObjectName, allocator);
	newObjectData.AddMember("translation", newObjectTranslation, allocator);
	newObjectData.AddMember("rotation", newObjectRotation, allocator);
	newObjectData.AddMember("scale", newObjectScale, allocator);
	newObjectData.AddMember("depth", newObjectDepth, allocator);
	newObjectData.AddMember("gravity", newObjectGravity, allocator);

	//rapidjson::Value::StringRefType objectname = rapidjson::StringRef(name.c_str());
	rapidjson::Value nameofobject(name.c_str(), allocator);

	//Add objectdata to document
	document.AddMember(nameofobject, newObjectData,allocator);
}

void JSON::ModifyObjectData(Object* object, std::string name)
{
	//const rapidjson::Value& object_data = document[name.c_str()];

	//assert(object_data.HasMember("translation"));
	//assert(object_data["translation"].IsArray());

	rapidjson::Value& a_type_data = document[name.c_str()]["translation"];
	//for (rapidjson::SizeType i = 0; i < data.Size(); i++)
	a_type_data[0].SetFloat(object->GetTransform().GetTranslation().x);
	a_type_data[1].SetFloat(object->GetTransform().GetTranslation().y);

	//assert(object_data.HasMember("rotation"));
	rapidjson::Value& o_type_data = document[name.c_str()]["rotation"];
	o_type_data = document[name.c_str()]["rotation"];
	o_type_data.SetFloat(*(object->GetTransform().GetRotation()));

	//a_type_data = document[name.c_str()]["scale"];
	document[name.c_str()]["scale"][0].SetFloat(object->GetTransform().GetScale().x);
	document[name.c_str()]["scale"][1].SetFloat(object->GetTransform().GetScale().y);

	//data = document[name.c_str()]["depth"];
	document[name.c_str()]["depth"].SetFloat(object->GetTransform().GetDepth());

	//data = document[name.c_str()]["gravity"];
	document[name.c_str()]["gravity"].SetFloat(object->GetGravity());
}

void JSON::StoreData()
{
	FILE *fp;
	fopen_s(&fp, "output.json", "wb");

	//char writeBuffer[65535];
	//rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	//rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);

	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
	document.Accept(writer);
	fclose(fp);
}