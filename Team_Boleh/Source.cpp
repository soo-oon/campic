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
#include "level1.hpp"
#include "StateManager.hpp"
#include "level2.hpp"
#include "MapEditorTest.hpp"
#include "StartMenu.hpp"
#include "SplashScreen.hpp"
#include "Demonstrate.hpp"

int main()
{
    Engine* engine = new Engine();

    engine->Initialize();

	engine->GetSystemByTemplate<StateManager>()->AddStage("Splash_Screen", new SplashScreen());
	engine->GetSystemByTemplate<StateManager>()->AddStage("StartMenu", new StartMenu());
	engine->GetSystemByTemplate<StateManager>()->AddStage("level1",new level1());
	engine->GetSystemByTemplate<StateManager>()->AddStage("level2", new level2());
	engine->GetSystemByTemplate<StateManager>()->AddStage("MapEditorTest", new MapEditorTest());
	engine->GetSystemByTemplate<StateManager>()->AddStage("Demonstrate", new Demonstrate());

    engine->Update();
  
    engine->ShutDown();

    return 0;
}
