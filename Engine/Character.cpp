/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Character.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Character.hpp"

void Character::SetCharType(ObjectType object_type)
{
	char_type = object_type;
}

ObjectType Character::GetCharType()
{
	return char_type;
}

bool Character::Initialize(Object * Ob)
{
	return false;
}

void Character::Update(float dt)
{
}

void Character::Delete()
{
}
