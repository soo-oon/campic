#pragma once
#include <vector>
#include "System.hpp"
#include "Timer.hpp"
#include "Objectmanager.hpp"

enum SystemList
{
    appication,
    statemanager,
    objectmanager,
};

class Engine
{
public:
    bool Initialize();
    void Update();
    void Quit();
    void ShutDown();

    System* GetSystem(unsigned ID) { return systems[ID]; }

    void AddSystem(System* new_system);

private:
    bool IsQuit = false;
    Timer gameTimer{};
    float dt = 0;
    std::vector<System*> systems;
};