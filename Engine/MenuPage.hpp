#pragma once

#include "Object.hpp"

class MenuPage
{
public:
	MenuPage() = default;
	~MenuPage() = default;

	std::vector<Object*>& GetButtons() { return buttons; }

	void InsertButtons(Object* obj) { buttons.push_back(obj); }

private:
	std::vector<Object*> buttons;
};