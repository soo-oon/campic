#pragma once
#include "Object.hpp"
#include "State.hpp"
#include "Objectmanager.hpp"

class Picking
{
public:

    void Initialize() ;
    void Update(float dt) ;
    void Quit() ;
private:
    Object* ActiveObject = nullptr;
};


extern Picking Picking_;