#include "Level3.hpp"
#include "Input.hpp"
#include "Animation.hpp"
#include <iostream>
#include "Particle_Generator.hpp"
#include "Camera.hpp"
#include "Font.hpp"
#include "Sound.hpp"
#include "Application.hpp"
#include "Tile_Map.hpp"
#include "Capture.hpp"
#include "Projectile.hpp"
#include "Player.hpp"
#include "MovingObject.hpp"
#include "UI.hpp"

void Level3::Initialize()
{
}

void Level3::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_0))
		BackToMenu();
}

void Level3::ShutDown()
{
	container.clear();
	UnLoad();
}
