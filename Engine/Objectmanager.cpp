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
#include <algorithm>
#include <cassert>
#include "Camera.hpp"
#include "Player.hpp"
#include <iostream>
#include "Physics.hpp"
#include "Capture.hpp"
#include "Engine.hpp"

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
	auto size = objects_.size();

	std::cout << size << std::endl;

	for (auto object = objects_.begin(); object != objects_.end();)
	{
		for (auto components : object->get()->GetComponent())
		{
			components->Update(dt);
		}

		if (size != objects_.size())
			break;

		SetPlayer(object->get());
		SetCaptureObject(object->get());

		if(object->get()->IsDead())
		{
			object = objects_.erase(object);
		}
		else
		{
			++object;
		}
	}
}

void Objectmanager::Quit()
{
	objects_.clear();
}

void Objectmanager::AddObject(Object* obj)
{
	std::shared_ptr<Object> temp(obj);

	objects_.push_back(temp);

 	for(auto component : objects_[objects_.size()-1]->GetComponent())
	{
		component->Initialize(objects_[objects_.size() - 1].get());
	}

	std::stable_sort(objects_.begin(), objects_.end(), 
		[](auto& obj1, auto& obj2) { return obj1->GetTransform().GetDepth() > obj2->GetTransform().GetDepth(); });
}

void Objectmanager::AddObject(std::shared_ptr<Object> obj)
{
	objects_.push_back(obj);

	for (auto component : objects_[objects_.size() - 1]->GetComponent())
	{
		component->Initialize(objects_[objects_.size() - 1].get());
	}

	std::stable_sort(objects_.begin(), objects_.end(),
		[](auto& obj1, auto& obj2) { return obj1->GetTransform().GetDepth() > obj2->GetTransform().GetDepth(); });
}

void Objectmanager::SetCaptureObject(Object* obj)
{
	if (obj->GetComponentByTemplate<Capture>() != nullptr)
	{
		StateManager_.GetCurrentState()->SetCaptureObjectPointer(obj);
	}
}

void Objectmanager::SetPlayer(Object* obj)
{
	if (obj->GetObjectType() == ObjectType::Player)
	{
		StateManager_.GetCurrentState()->SetPlayerObjectPointer(obj);
	}
}

void Objectmanager::RemoveObject()
{
	//std::cout << "Before: " << objects_.size() << std::endl;
	//auto check = StateManager_.GetCurrentState()->GetPlayerPointer();
	//auto sibal = check->GetComponentByTemplate<Capture>()->GetCaptureObject();

	objects_.clear();

	std::cout << "After: " << objects_.size() << std::endl;

	//std::cout << objects_.size() << std::endl;
}
