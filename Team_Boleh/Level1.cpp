#include "Level1.hpp"
#include "Input.hpp"
#include "Font.hpp"
#include "Application.hpp"
#include "Tile_Map.hpp"

void Level1::Initialize()
{
	//LoadLevel();
}

void Level1::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_R))
	{
		ChangeLevel("Level1");
	}

	if (Input::IsKeyTriggered(GLFW_KEY_I))
		Tile_Map_.Delete_Tile();
}

void Level1::ShutDown()
{
	UnLoad();
}
