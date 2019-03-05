#pragma once
#include "State.hpp"

class Room1 : public State
{
public:
    Room1()
    {
        information_ = State_Information::Game;
    }
    void Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;

private:
    Object *store;
    Object *room2;
    Object *room;
    Object *enemy;
};

