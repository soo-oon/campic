/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Objectmanager.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Objectmanager.hpp"
#include <cassert>
#include "Camera.hpp"
#include "Player.hpp"
#include "Sword.hpp"
#include "Status.hpp"
#include <iostream>

Objectmanager Objectmanager_;

bool Objectmanager::Initialize()
{
	if(!objects_.empty())
	{
		for (auto& obj : objects_)
		{
			for (auto& component : obj->GetComponent())
			{
				component->Initialize(obj.get());
			}
		}
	}

	return true;
}

void Objectmanager::Update(float dt)
{
	for (auto object = objects_.begin(); object != objects_.end();)
	{
		for (auto components : object->get()->GetComponent())
		{
			components->Update(dt);
		}

		if (!object->get()->GetComponentByTemplate<Status>()->IsLive())
		{
			object = objects_.erase(object);
		}
		else
		{
			object++;
		}
	}

	/*
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

		if(obj->GetComponentByTemplate<FireBall>() != nullptr)
		{
			obj->GetComponentByTemplate<FireBall>()->Update(dt);
			if(obj->GetComponentByTemplate<FireBall>()->IsDead())
				will_remove_object.push_back(it->first);
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
		
	}
	for (auto erase_object : will_remove_object)
	{
		object_map.erase(erase_object);
	}
	will_remove_object.clear();
	*/
}

void Objectmanager::Quit()
{
	objects_.clear();
}

void Objectmanager::AddObject(Object obj)
{
	auto temp_obj = std::make_unique<Object>(obj);

	objects_.push_back(std::move(temp_obj));
}

void Objectmanager::RemoveObject()
{
	for(auto object = objects_.begin(); object != objects_.end();)
	{
		if(object->get()->GetComponentByTemplate<Status>()->GetObjectType() != ObjectType::Player &&
			object->get()->GetComponentByTemplate<Status>()->GetObjectType() != ObjectType::Sword)
		{
			object = objects_.erase(object);
		}
		else
		{
			object++;
		}
	}

	std::cout << objects_.size() << std::endl;
}

//void Objectmanager::RemoveObject(std::string key_name)
//{
//    auto object(std::make_unique<Object>());
//    auto found = object_map.find(key_name);
//    if (found != object_map.end())
//    {
//        object = std::move(found->second);
//        object_map.erase(found);
//    }
//}

//bool Objectmanager::IsExistPlayer()
//{
//	auto found = object_map.find("Player");
//
//	if (found == object_map.end())
//	{
//		return false;
//	}
//	return true;
//}

//std::unique_ptr<Object>& Objectmanager::FindObject(std::string key_name)
//{
//    auto found = object_map.find(key_name);
//
//    if (found == object_map.end())
//    {
//        assert(false);
//    }
//    return found->second;
//}

//int Objectmanager::FindMaxID()
//{
//	int max = 0;
//	for (auto itr = object_map.begin(); itr != object_map.end(); itr++)
//	{
//		if (itr->second != nullptr)
//		{
//			if (max < itr->second.get()->object_id)
//				max = itr->second.get()->object_id;
//		}
//	}
//	return max;
//}