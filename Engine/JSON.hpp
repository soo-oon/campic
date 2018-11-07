#pragma once
#include "document.h"
//#include "writer.h"
#include "filewritestream.h"
#include "filereadstream.h"
#include "Objectmanager.hpp"
#include "prettywriter.h"


class JSON : public System
{
public:
	bool Initialize() override;
	void Update(float dt) override {};
	void Quit() override;

	void UpdateData(Objectmanager* objectmanager);

	void AddNewObjectData(Object* object, std::string name);
	void ModifyObjectData(Object* object, std::string name);

	void LoadData();
	void StoreData();

private:
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	const char* file_name = "output.json";
	void SendData(Object* object, std::string name);

};