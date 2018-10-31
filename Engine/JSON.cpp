#include "JSON.hpp"

bool RJSON::Initialize()
{
	document.SetObject();
	if (!document.IsObject())
		return false;
	return true;
}

void RJSON::ObjectCreateData(Objectmanager* objectmanager, std::string name)
{
	rapidjson::Value newObjectData(rapidjson::kObjectType);
	Object* currentObject = nullptr;
	for (std::map<std::string, std::unique_ptr<Object>>::iterator it = objectmanager->GetObjectMap().begin();
		it != objectmanager->GetObjectMap().end(); ++it)
	{
		if ((*it).first == name)
		{
			currentObject = it->second.get();
			break;
		}

	}

	if (currentObject == nullptr)
		return;

	rapidjson::Value newObjectName(name.c_str(), allocator);

	rapidjson::Value newObjectTranslation(rapidjson::kArrayType);
	newObjectTranslation.PushBack(currentObject->GetTransform().GetTranslation().x, allocator);
	newObjectTranslation.PushBack(currentObject->GetTransform().GetTranslation().y, allocator);

	rapidjson::Value newObjectScale(rapidjson::kArrayType);
	newObjectScale.PushBack(currentObject->GetTransform().GetScale().x, allocator);
	newObjectScale.PushBack(currentObject->GetTransform().GetScale().y, allocator);

	rapidjson::Value newObjectRotation(rapidjson::kObjectType);
	newObjectScale.SetFloat(*(currentObject->GetTransform().GetRotation()));

	rapidjson::Value newObjectDepth(rapidjson::kObjectType);
	newObjectScale.SetFloat(currentObject->GetTransform().GetDepth());

	rapidjson::Value newObjectGravity(rapidjson::kObjectType);
	newObjectGravity.SetFloat(currentObject->GetGravity());

	newObjectData.AddMember("name", newObjectName, allocator);
	newObjectData.AddMember("transltaion", newObjectTranslation, allocator);
	newObjectData.AddMember("scale", newObjectScale, allocator);
	newObjectData.AddMember("depth", newObjectDepth, allocator);
	newObjectData.AddMember("gravity", newObjectGravity, allocator);

	rapidjson::Value::StringRefType objectname = rapidjson::StringRef(name.c_str());

	document.AddMember(objectname, newObjectData, allocator);
}

//void RJSON::StoreData()
//{
//	FILE *fp;
//	fopen_s(&fp, "output.json", "wb");
//	char writeBuffer[65535];
//	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
//	Writer<FileWriteStream> writer(os);
//	document.Accept(writer);
//	fclose(fp);
//}