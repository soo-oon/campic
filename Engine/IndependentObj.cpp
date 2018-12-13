#include "IndependentObj.hpp"
#include "Player.hpp"
#include "Sword.hpp"

bool IndependentObj::Initialize()
{
	player->AddComponent(new Player());
	sword->AddComponent(new Sword(player.get()));

	return true;
}

void IndependentObj::Update(float dt)
{
}

void IndependentObj::Quit()
{
}
