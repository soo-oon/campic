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