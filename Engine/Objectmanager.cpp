#include "Objectmanager.hpp"
#include <cassert>

bool Objectmanager::Initialize() { return true; }

void Objectmanager::Update(float dt)
{
	
}

void Objectmanager::Quit()
{
	object_map.clear();
}

void Objectmanager::AddObject(std::string key_name)
{
    if (object_map.find(key_name) == object_map.end())
        object_map.insert(std::make_pair(key_name, std::make_unique<Object>()));
    else
        assert(false);
}

void Objectmanager::RemoveObject(std::string key_name)
{
    auto object(std::make_unique<Object>());
    auto found = object_map.find(key_name);
    if (found != object_map.end())
    {
        object = std::move(found->second);
        object_map.erase(found);
    }
}

std::unique_ptr<Object>& Objectmanager::FindObject(std::string key_name)
{
    auto found = object_map.find(key_name);

    if (found == object_map.end())
    {
        assert(false);
    }
    return found->second;
}
