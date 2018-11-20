#include "Objectmanager.hpp"
#include <cassert>
#include "Camera.hpp"

bool Objectmanager::Initialize() { return true; }

void Objectmanager::Update(float dt)
{
	for (std::map<std::string, std::unique_ptr<Object>>::iterator it = object_map.begin();
		it != object_map.end(); ++it)
	{
		Object obj = *(it->second.get());

		if(obj.GetComponentByTemplate<Sprite>() != nullptr)
		{
			obj.GetComponentByTemplate<Sprite>()->Update(dt);
		}

		if(obj.GetComponentByTemplate<Animation>() != nullptr)
		{
			obj.GetComponentByTemplate<Animation>()->Update(dt);
		}

		if (obj.GetComponentByTemplate<Camera>() != nullptr)
		{
			obj.GetComponentByTemplate<Camera>()->Update(dt);
		}
	}
}

void Objectmanager::Quit()
{
	object_map.clear();
}

void Objectmanager::AddObject(std::string key_name)
{
	if (object_map.find(key_name) == object_map.end())
	{
		object_map.insert(std::make_pair(key_name, std::make_unique<Object>()));
	}

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

bool Objectmanager::FindCameraObject()
{
	for (std::map<std::string, std::unique_ptr<Object>>::iterator it = object_map.begin();
		it != object_map.end(); ++it)
	{
		Object obj = *(it->second.get());

		if (obj.GetComponentByTemplate<Camera>() != nullptr)
			return true;
		else
			return false;
	}

	return false;
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
