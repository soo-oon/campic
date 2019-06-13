/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  Source.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Application.hpp"
#include "Engine.hpp"
#include "StateManager.hpp"
#include "SplashScreen.hpp"
#include "MainMenu.hpp"
#include "Level.hpp"
#include "LevelSelector.hpp"
#include "Credit.hpp"
#include "HowToPlay.hpp"
#include "StartCutScene.hpp"
#include "EndCutScene.hpp"

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(25697);

    Engine engine;

    engine.Initialize();
    
    StateManager_.AddStage("Splash_Screen", new SplashScreen());
	
	StateManager_.AddStage("MainMenu", new MainMenu());
	StateManager_.AddStage("HowToPlay", new HowToPlay());
	StateManager_.AddStage("LevelSelector", new LevelSelector());
	StateManager_.AddStage("StartCutScene", new StartCutScene());
	StateManager_.AddStage("EndCutScene", new EndCutScene());
	StateManager_.AddStage("Credit", new Credit());
	StateManager_.AddStage("Level", new Level());

	engine.Update();
  
    engine.Quit();


    return 0;
}
