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
#include "State.hpp"
#include "AudioManager.hpp"
#include "Physics.hpp"
#include "Imgui_System.hpp"
#include "JSON.hpp"
#include "HUD.hpp"

bool Engine::IsQuit;

bool Engine::Initialize()
{
	System_Initialize();

	//hud_state = HUD_->GetHUDlevel();
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

		//Physics_->PhysicsObjectUpdate(Objectmanager_);

		//HUD_->SetObjectManager(Objectmanager_);

		//Graphics_->HUD_Draw(Objectmanager_);
		//Graphics_.Draw(&Objectmanager_);

		Graphics_.Draw();
		Graphics_.EndDraw();
		IMGUI_.Draw();

		//Json->UpdateLevel(GetSystemByTemplate<StateManager>());
		//Json->UpdateState(GetSystemByTemplate<StateManager>());

        if (Input::IsKeyTriggered(GLFW_KEY_ESCAPE))
            IsQuit = true;
    }

    Quit();
}

void Engine::Quit()
{
	//JSON_.SaveAtEnd();
	System_Quit();
}

void Engine::System_Initialize()
{
	Application_.Initialize();
	StateManager_.Initialize();
	Objectmanager_.Initialize();
	Graphics_.Initialize();
	IMGUI_.Initialize();
	AudioManager_.Initialize();
	Physics_.Initialize();
	JSON_.Initialize();

	//TODO make new HUD structure 
	//HUD_.Initialize();
	
}

void Engine::System_Update()
{
	Application_.Update(dt);
	StateManager_.Update(dt);
	Objectmanager_.Update(dt);
	Graphics_.Update(dt);
	IMGUI_.Update(dt);
	AudioManager_.Update(dt);
	JSON_.Update(dt);

	// Should Fix All of Update ways (Should Fix Physics class structure)
	Physics_.Update(dt);

	//TODO make new HUD structure 
	//HUD_.Update(dt);
}

void Engine::System_Quit()
{
	Application_.Quit();
	StateManager_.Quit();
	Objectmanager_.Quit();
	Graphics_.Quit();
	IMGUI_.Quit();
	AudioManager_.Quit();
	Physics_.Quit();
	JSON_.Quit();

	//HUD_.Quit();
}
