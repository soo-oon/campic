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

#include "Application.hpp"
#include "Engine.hpp"
#include "StateManager.hpp"
#include "SplashScreen.hpp"
#include "MainMenu.hpp"
#include "Level.hpp"
#include "LevelSelector.hpp"
#include "Test_Level.hpp"

int main()
{
    Engine engine;

    engine.Initialize();
    
    /*StateManager_->AddStage("Splash_Screen", new SplashScreen());
    StateManager_->AddStage("StartMenu", new StartMenu());
    StateManager_->AddStage("level1",new level1());
    StateManager_->AddStage("level2", new level2());
    StateManager_->AddStage("MapEditorTest", new MapEditorTest());
    StateManager_->AddStage("Demonstrate", new Demonstrate());*/

	//StateManager_.AddStage("MainMenu", new MainMenu());
	//StateManager_.AddStage("LevelSelector", new LevelSelector());
	//StateManager_.AddStage("Level", new Level());
	StateManager_.AddStage("Test_Level", new Test_Level());


	engine.Update();
  
    engine.Quit();

    return 0;
}
