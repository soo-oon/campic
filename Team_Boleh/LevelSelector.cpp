#include "LevelSelector.hpp"

void LevelSelector::Initialize()
{
	LoadLevel(current_level);
}

void LevelSelector::Update(float dt)
{


}

void LevelSelector::ShutDown()
{
	UnLoad();
}
