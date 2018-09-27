#pragma once
#include <vector>
#include "Component.hpp"

class Object
{
public:
	void AddComponent(Component* component);

private:
	Transform transform{};
	std::vector<Component*> components;
};