#include "Objectmanager.hpp"
#include <cassert>
#include "Camera.hpp"
#include "status.hpp"
#include "Player.hpp"

bool Objectmanager::Initialize()
{
	if(!object_map.empty())
	{
		for (std::map<std::string, std::unique_ptr<Object>>::iterator it = object_map.begin();
			it != object_map.end(); ++it)
		{
			Object* obj = it->second.get();
			if (obj->GetComponentByTemplate<Sprite>() != nullptr)
			{
				obj->GetComponentByTemplate<Sprite>()->Initialize(obj);
			}
			if (obj->GetComponentByTemplate<RigidBody>() != nullptr)
			{
				obj->GetComponentByTemplate<RigidBody>()->Initialize(obj);
			}
			if (obj->GetComponentByTemplate<Collision>() != nullptr)
			{
				obj->GetComponentByTemplate<Collision>()->Initialize(obj);
			}


			if (obj->GetComponentByTemplate<Animation>() != nullptr)
			{
				obj->GetComponentByTemplate<Animation>()->Initialize(obj);
			}

			if (obj->GetComponentByTemplate<Camera>() != nullptr)
			{
				obj->GetComponentByTemplate<Camera>()->Initialize(obj);
			}
			if (obj->GetComponentByTemplate<Player>() != nullptr)
			{
				obj->GetComponentByTemplate<Player>()->Initialize(obj);
			}

			if (obj->GetComponentByTemplate<Status>() != nullptr)
			{
				obj->GetComponentByTemplate<Status>()->Initialize(obj);
				if (obj->GetComponentByTemplate<Status>()->GetLived() == false)
				{
					object_map.erase(it++);
				}
			}
		}
	}
	
	return true;
}

void Objectmanager::Update(float dt)
{
	for (std::map<std::string, std::unique_ptr<Object>>::iterator it = object_map.begin();
		it != object_map.end(); ++it)
	{
		Object* obj = it->second.get();

		if(obj->GetComponentByTemplate<Sprite>() != nullptr)
		{
			obj->GetComponentByTemplate<Sprite>()->Update(dt);
		}

		if(obj->GetComponentByTemplate<Animation>() != nullptr)
		{
			obj->GetComponentByTemplate<Animation>()->Update(dt);
		}

		if (obj->GetComponentByTemplate<Camera>() != nullptr)
		{
			obj->GetComponentByTemplate<Camera>()->Update(dt);
		}
		if (obj->GetComponentByTemplate<Player>() != nullptr)
		{
			obj->GetComponentByTemplate<Player>()->Update(dt);
		}

		if(obj->GetComponentByTemplate<Status>() != nullptr)
		{
			obj->GetComponentByTemplate<Status>()->Update(dt);
			if (obj->GetComponentByTemplate<Status>()->GetLived() == false)
			{
				object_map.erase(it++);
			}
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

bool Objectmanager::IsExistPlayer(std::string player)
{
	auto found = object_map.find(player);

	if (found == object_map.end())
	{
		return false;
	}
	return true;
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

int Objectmanager::FindMaxID()
{
	int max = 0;
	for (auto itr = object_map.begin(); itr != object_map.end(); itr++)
	{
		if (max < itr->second.get()->object_id)
			max = itr->second.get()->object_id;
	}
	return max;
}