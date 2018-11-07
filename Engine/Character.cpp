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
