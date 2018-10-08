#pragma once
#include <vector>
#include "System.hpp"
#include "Timer.hpp"
#include "Objectmanager.hpp"

enum SystemList
{
    appication,
    statemanager,
    //objectmanager,
	graphics
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
    static bool IsQuit;

private:
    Timer gameTimer{};
    float dt = 0;
    std::vector<System*> systems;
};