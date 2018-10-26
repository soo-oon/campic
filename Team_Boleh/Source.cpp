#include "Application.hpp"
#include "Engine.hpp"
#include "example_level.hpp"
#include "StateManager.hpp"
#include "statemanager_test.hpp"

int main()
{
    Engine* engine = new Engine();

    engine->Initialize();

	engine->GetSystemByTemplate<StateManager>()->AddStage("example",new example());
	engine->GetSystemByTemplate<StateManager>()->AddStage("test", new test_statemanager());

    engine->Update();
  
    engine->ShutDown();

    return 0;
}
