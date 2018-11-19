#pragma once
#include "State.hpp"
#include "Objectmanager.hpp"
#include "Object.hpp"

class MapEditor : public System
{
public:
	bool Initialize() override;
	void Update(float dt) override;
	void Quit() override;

	void LoadMap();

private:
	int object_count = 1;
	std::string object_name = "object";
	std::vector<Object*> objects;
	Object* newObject;
	Object* selected_object = nullptr;
};
