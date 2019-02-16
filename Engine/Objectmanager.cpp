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

		if (auto temp = object->get()->GetComponentByTemplate<Status>(); temp != nullptr)
		{
            if (!temp->IsAlive())
                object = objects_.erase(object);
            else
                ++object;
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

void Objectmanager::AddObject(Object obj)
{
	objects_.push_back(std::make_unique<Object>(obj));

	std::cout << objects_.size() << std::endl;

	for(unsigned int i =0; i<objects_.size(); ++i)
	{
	    for(auto component : objects_[i]->GetComponent())
	    {
		    component->Initialize(objects_[i].get());
	    }
	}
}

void Objectmanager::RemoveObject()
{
	for(auto object = objects_.begin(); object != objects_.end();)
	{
		if(auto temp = object->get()->GetComponentByTemplate<Status>();
                    temp == nullptr ||(
                    temp->GetObjectType() != ObjectType::Player &&
                    temp->GetObjectType() != ObjectType::Sword))
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
