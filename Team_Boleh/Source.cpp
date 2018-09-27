#include "Application.hpp"
#include "Engine.hpp"
#include "example_level.hpp"
#include "StateManager.hpp"

int main()
{
    Engine* engine = new Engine();

    engine->Initialize();

    dynamic_cast<StateManager*>(engine->GetSystem(SystemList::statemanager))->AddStage(new example());

    engine->Update();
  
    engine->ShutDown();

    return 0;
}
