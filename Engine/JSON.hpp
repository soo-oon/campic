#pragma once
#include "document.h"
#include "writer.h"
#include "filewritestream.h"
#include "Objectmanager.hpp"
#include "prettywriter.h"
//#include "stringbuffer.h"

class JSON : public System
{
public:
	bool Initialize() override;
	void Update(float dt) override {};
	void Quit() override;

	//void ObjectCreateData(Objectmanager* objectmanager, std::string name);

	void UpdateData(Objectmanager* objectmanager);

	void SendData(Object* object, std::string name);
	void AddNewObjectData(Object* object, std::string name);
	void ModifyObjectData(Object* object, std::string name);

	void StoreData();

private:
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	const char* file_name = "output.json";
};