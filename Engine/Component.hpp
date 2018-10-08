#pragma once

enum ComponentType
{
    clear,
    sprite,
    physics,
    animation
};

class Object;

class Component
{
private:
public:
    virtual ~Component()
    {
    };
    ComponentType type = clear;
    Object* object;

    virtual bool Initialize(Object* Ob) = 0;
    virtual void Update(float dt) = 0;
    virtual void Delete() = 0;
};
