/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Card.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jung Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
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
