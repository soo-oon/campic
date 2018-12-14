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

#include "Card.hpp"
#include "Character.hpp"

Card::Card(std::string name)
{
	card_name = name;
}

bool Card::Initialize(Object * Ob)
{
	return false;
}

void Card::Update(float dt)
{
}

void Card::Delete()
{
}

std::string Card::GetName()
{
	return card_name;
}
