#pragma once

class System
{
public:
    virtual ~System() = default;

    virtual bool Initialize() = 0;
    virtual void Update(float dt) = 0;
    virtual void Quit() = 0;

};