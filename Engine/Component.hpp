#pragma once


class Object;

class Component
{
private:
public:
    virtual ~Component()
    {
    };
    Object* object;

    virtual bool Initialize(Object* Ob) = 0;
    virtual void Update(float dt) = 0;
    virtual void Delete() = 0;
};
