#pragma once
#include "Component.hpp"

enum class TriggerStyle
{
    Door,
    Font,
    None
};

class Trigger : public Component
{
public:
    Trigger(Object* connect) : m_connected_object(connect){}

    bool Initialize(Object* Ob);
    void Update(float dt);
    void Delete();

public:
    //When you make function and style, input in this function.
    void ConnectObjectAction();

    void SetIsTriggerd(bool trigger) { isTriggered = trigger; }

    bool GetIsTriggerd() { return isTriggered; }
private:

    //When you want to use trigger, you should make Triggerstyle and function that you want to apply.

    TriggerStyle m_trigger_style = TriggerStyle::None;
    Object* m_connected_object = nullptr;
    bool isTriggered = false;
};

