#pragma once
#include "Object.hpp"
#include <map>
#include <string>
#include "System.hpp"

class Objectmanager : public System
{
public:
	bool Initialize() ;
	void Update(float dt) ;
	void Quit() ;
	void AddObject(std::string key_name);
	void RemoveObject(std::string key_name);
	Object* FindObject(std::string key_name);
	std::map<std::string, Object*>& GetObjectMap() { return object_map; }
private:
	std::map<std::string,Object*> object_map;
};
