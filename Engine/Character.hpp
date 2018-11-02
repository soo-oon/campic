#pragma once
#include "Component.hpp"

enum class ObjectType
{
	player,
	opponent,
	sword,
	wall,
	NONE,
};

class Character
{
public:

	void SetCharType(ObjectType object_type);
	ObjectType GetCharType();
	bool Initialize(Object* Ob);
	void Update(float dt);
	void Delete();
private:
	ObjectType char_type = ObjectType::NONE;
};