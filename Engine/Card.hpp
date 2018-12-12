#pragma once
#include "Component.hpp"
#include <string>

class Card : public Component
{
public:
	Card(std::string name);
	bool Initialize(Object* Ob);
	void Update(float dt);
	void Delete();
	std::string GetName();
private:
	std::string card_name;
};
