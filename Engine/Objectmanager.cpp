#include "Objectmanager.hpp"
#include <cassert>

bool Objectmanager::Initialize() { return true; }
void Objectmanager::Update(float dt)
{}
void Objectmanager::Quit(){}
void Objectmanager::AddObject(std::string key_name)
{
	Object* object = new Object;
	if (object_map.find(key_name) == object_map.end())
		object_map.insert(std::make_pair(key_name, object));
	else
		assert(false);
}

void Objectmanager::RemoveObject(std::string key_name)
{
	Object* object;
	auto found = object_map.find(key_name);

	if (found != object_map.end())
	{
		object = found->second;
		delete object;
		object_map.erase(found);
	}
}

Object* Objectmanager::FindObject(std::string key_name)
{
	auto found = object_map.find(key_name);

	if (found != object_map.end())
	{
		return found->second;
	}
	return nullptr;
}
