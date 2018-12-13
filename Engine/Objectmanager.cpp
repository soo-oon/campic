#include "Objectmanager.hpp"
#include <cassert>
#include "Camera.hpp"
#include "status.hpp"
#include "Player.hpp"
#include "Sword.hpp"

bool Objectmanager::Initialize()
{
	if(!object_map.empty())
	{
		for (std::map<std::string, std::unique_ptr<Object>>::iterator it = object_map.begin();
			it != object_map.end(); ++it)
		{
			Object* obj = it->second.get();

			for (auto& component : obj->GetComponent())
			{
				component->Initialize(obj);
			}

			/*if (obj->GetComponentByTemplate<Sprite>() != nullptr)
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

			if(obj->GetComponentByTemplate<Sword>() != nullptr)
			{
				obj->GetComponentByTemplate<Sword>()->Initialize(obj);
			}

			if (obj->GetComponentByTemplate<Player>() != nullptr)
			{
				obj->GetComponentByTemplate<Player>()->Initialize(obj);
			}
*/
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


		for(auto& component : obj->GetComponent())
		{
			component->Update(dt);
		}

		if (obj->GetComponentByTemplate<Status>() != nullptr)
		{
			//obj->GetComponentByTemplate<Status>()->Update(dt);
			if (obj->GetComponentByTemplate<Status>()->GetLived() == false)
			{
				if (obj->GetComponentByTemplate<Player>() == nullptr)
					will_remove_object.push_back(it->first);
			}
		}
		if (obj->GetComponentByTemplate<Collision>() != nullptr)
		{
			//obj->GetComponentByTemplate<Status>()->Update(dt);
			if (obj->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::get)
			{
				if(obj->GetComponentByTemplate<Player>() == nullptr)
					will_remove_object.push_back(it->first);
			}
		}
		/*if(obj->GetComponentByTemplate<Sprite>() != nullptr)
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

		if(obj->GetComponentByTemplate<Sword>() != nullptr)
		{
			obj->GetComponentByTemplate<Sword>()->Update(dt);
		}
*/
	}
	for (auto erase_object : will_remove_object)
	{
		object_map.erase(erase_object);
	}
	will_remove_object.clear();
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

bool Objectmanager::IsExistPlayer()
{
	auto found = object_map.find("Player");

	if (found == object_map.end())
	{
		return false;
	}
	return true;
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
		if (itr->second != nullptr)
		{
			if (max < itr->second.get()->object_id)
				max = itr->second.get()->object_id;
		}
	}
	return max;
}