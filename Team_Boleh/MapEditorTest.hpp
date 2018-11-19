#pragma once
#include "State.hpp"

class MapEditorTest : public State
{
public:
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

private:
	int object_count = 0;
	std::string object_name = "object";
	std::vector<Object*> objects;
	Object* newObject;
	Object* selected_object = nullptr;
};