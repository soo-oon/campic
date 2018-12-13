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
	bool FindCameraObject();

    std::unique_ptr<Object>& FindObject(std::string key_name);
    std::map<std::string, std::unique_ptr<Object>>& GetObjectMap() { return object_map; }
	int FindMaxID()
	{
		int max = 0;
		//Object* max_obj;
		for (auto itr = object_map.begin(); itr != object_map.end(); itr++)
		{
			//if (max < itr->second.get()->object_id)
			//{
			//	max = itr->second.get()->object_id;
			//	//max_obj = itr->second.get();
			//}
		}
		return 0;
	}

private:
    std::map<std::string, std::unique_ptr<Object>> object_map;
};
