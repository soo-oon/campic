/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Engine.hpp"
#include "Application.hpp"
#include "StateManager.hpp"
#include "Graphics.hpp"
#include "Input.hpp"
#include "AudioManager.hpp"
#include "Physics.hpp"
#include "Imgui_System.hpp"
#include "JSON.hpp"
#include "HUD.hpp"
#include "HUD_Level.hpp"
#include "Tile_Map.hpp"

bool Engine::IsQuit;

bool Engine::Initialize()
{
	System_Initialize();

    gameTimer.Reset();
    IsQuit = false;
	srand(static_cast<unsigned int>(time(NULL)));
    return true;
}

void Engine::Update()
{
    while (!IsQuit)
    {
        dt = (float)gameTimer.GetElapsedSeconds();
        gameTimer.Reset();

		System_Update();

		Graphics_.BeginDraw();
		Graphics_.Draw();
		Graphics_.Tile_Draw();
		Graphics_.HUD_Draw();
		Graphics_.EndDraw();
		IMGUI_.Draw();

        //if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
            //IsQuit = true;
    }

    Quit();
}

void Engine::Quit()
{
	System_Quit();
}

void Engine::System_Initialize()
{
	Application_.Initialize();
	StateManager_.Initialize();
	Graphics_.Initialize();
	Objectmanager_.Initialize();
	IMGUI_.Initialize();
	AudioManager_.Initialize();
	Physics_.Initialize();
 	HUD_.Initialize(new HUD_Level());
	JSON_.Initialize();

	//TODO make new HUD structure 
	
}

void Engine::System_Update()
{
	Application_.Update(dt);
	StateManager_.Update(dt);
	Graphics_.Update(dt);
        Physics_.Update(dt);
	Objectmanager_.Update(dt);
	IMGUI_.Update(dt);
	AudioManager_.Update(dt);
	JSON_.Update(dt);
	HUD_.Update(dt);

	Tile_Map_.Update(dt);
	// Should Fix All of Update ways (Should Fix Physics class structure)

	//TODO make new HUD structure 
}

void Engine::System_Quit()
{
	Application_.Quit();
	StateManager_.Quit();
	Graphics_.Quit();
	Objectmanager_.Quit();
	//IMGUI_.Quit();
	AudioManager_.Quit();
	Physics_.Quit();
	JSON_.Quit();

	//HUD_.Quit();
}
