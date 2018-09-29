#pragma once
#include "Objectmanager.hpp"

enum StageList
{
	splash,

};

class State
{
public:
    virtual ~State() {};
    //virtual void Load() = 0;
    virtual bool Initialize() = 0;
    virtual void Update(float dt) = 0;
    virtual void ShutDown() = 0;
    //virtual void Unload() = 0;
};