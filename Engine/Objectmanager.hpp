/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Objectmanager.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "Object.hpp"
#include <map>
#include <string>
#include <memory>

class Objectmanager
{
public:
	Objectmanager()
	{
		objects_.clear();
	}

    bool Initialize();
    void Update(float dt);
    void Quit();
	void AddObject(Object* obj);
	void RemoveObject();
	std::vector<std::shared_ptr<Object>>& GetObjectMap() { return objects_; }
	std::vector<Object>& GetCaptureObject() { return capture_obj; }

private:
	std::vector<std::shared_ptr<Object>> objects_;
	std::vector<Object> capture_obj;
};

extern Objectmanager Objectmanager_;