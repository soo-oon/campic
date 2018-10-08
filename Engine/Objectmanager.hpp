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
    std::unique_ptr<Object>& FindObject(std::string key_name);
    std::map<std::string, std::unique_ptr<Object>>& GetObjectMap() { return object_map; }
private:
    std::map<std::string, std::unique_ptr<Object>> object_map;
};
