#include "Trigger.h"

bool Trigger::Initialize(Object * Ob)
{
    object = Ob;
    return false;
}

void Trigger::Update(float dt)
{
    ConnectObjectAction();
}

void Trigger::Delete()
{
}

void Trigger::ConnectObjectAction()
{
    switch (m_trigger_style)
    {
    case TriggerStyle::Door:
        break;
    case TriggerStyle::Font:
        break;
    default:
        break;
    }
}
