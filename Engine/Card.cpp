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
