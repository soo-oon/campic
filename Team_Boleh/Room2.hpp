#pragma once
#include "State.hpp"

class Room2 : public State
{
public:
    Room2()
    {
        information_ = State_Information::Game;
    }
    void Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;

private:
    Object *room1;
    Object *boss_room;
    Object *enemy;
};

