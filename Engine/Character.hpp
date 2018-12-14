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

#pragma once
#include "Component.hpp"

enum class ObjectType
{
	player,
	opponent,
	sword,
	wall,
	card,
	door,
	shot,
	none,
};

class Character : public Component
{
public:
	Character(ObjectType object_type):char_type(object_type) {}
	void SetCharType(ObjectType object_type);
	ObjectType GetCharType();
	bool Initialize(Object* Ob);
	void Update(float dt);
	void Delete();
private:
	ObjectType char_type;
};