#include "Application.hpp"
#include "Engine.hpp"
#include "example_level.hpp"
#include "StateManager.hpp"

int main()
{
    Engine engine;

    engine.Initialize();

    auto check = new example();
    dynamic_cast<StateManager*>(engine.GetSystem(SystemList::statemanager))->AddStage(check);
    dynamic_cast<StateManager*>(engine.GetSystem(SystemList::statemanager))->SetCurrentStage(check);

    engine.Update();
  
    engine.ShutDown();

    return 0;
}
