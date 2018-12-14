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
#include "System.hpp"
#include <memory>

class Objectmanager : public System
{
public:
    bool Initialize() override;
    void Update(float dt) override;
    void Quit() override;
    void AddObject(std::string key_name);
    void RemoveObject(std::string key_name);

	bool IsExistPlayer();

    std::unique_ptr<Object>& FindObject(std::string key_name);
    std::map<std::string, std::unique_ptr<Object>>& GetObjectMap() { return object_map; }
	std::map<std::string, std::unique_ptr<Object>>* GetObjectMapPointer() { return &object_map; }
	int FindMaxID();

private:
	std::map<std::string, std::unique_ptr<Object>> object_map;
	std::vector <std::string > will_remove_object;
    //std::map<std::string, std::unique_ptr<Object>> object_map;
};
