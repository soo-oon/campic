#pragma once
#include "document.h"
//#include "stringbuffer.h"
//#include "writer.h"
#include "Objectmanager.hpp"

class RJSON// : public System
{
public:
	bool Initialize();
	void Update() {};
	void Quit() {};

	void ObjectCreateData(Objectmanager* objectmanager, std::string name);

	void StoreData();

private:
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
};