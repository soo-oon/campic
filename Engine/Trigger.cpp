#include "Trigger.h"
#include "ObjectDepth.hpp"
#include "State.hpp"
#include "Capture.hpp"

bool Trigger::Initialize(Object * Ob)
{
    object = Ob;
    return false;
}

void Trigger::Update(float dt)
{
    ConnectObjectAction();
    switch (m_trigger_style)
    {
    case TriggerStyle::Door:
        break;
    case TriggerStyle::Font:
        break;
    case TriggerStyle::CheckPoint:
    {
        if (!m_connected_object)
        {
            m_connected_object = new Object;
            m_connected_object->SetTranslation(object->GetTransform().GetTranslation());
            m_connected_object->SetScale({ 100.f,100.f });
            m_connected_object->SetMesh(mesh::CreateBox(1, { 255,255,0, 255 }));
            m_connected_object->SetDepth(GAME_OBJECT);
            m_connected_object->SetObjectType(ObjectType::Trigger_Obj);
            m_connected_object->AddInitComponent(new Animation("asset/images/SavePoint.png", "sPoint", 17, 0.075f, true));
            m_connected_object->GetComponentByTemplate<Animation>()->SetIsActive(false);
            //m_connected_object->AddComponent(new Collision());
            Objectmanager_.AddObject(m_connected_object);
        }}
        break;
    default:
        break;
    }
}

void Trigger::Delete()
{
}

void Trigger::ConnectObjectAction()
{
    if (isTriggered)
    {
        switch (m_trigger_style)
        {
        case TriggerStyle::Door:
            MakeConnectedDoor();
            break;
        case TriggerStyle::Font:
            break;
        case TriggerStyle::CheckPoint:
            CheckPoint();
            break;
        default:
            break;
        }
    }
}

void Trigger::MakeConnectedDoor()
{
    if(!m_connected_object)
    {
        m_connected_object = new Object;
        m_connected_object->SetTranslation(o_translation);
        m_connected_object->SetScale({ 75.f,75.f });
        m_connected_object->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
        m_connected_object->SetDepth(GAME_OBJECT);
        m_connected_object->SetObjectType(ObjectType::Trigger_Obj);
        m_connected_object->AddComponent(new Collision());
        Objectmanager_.AddObject(m_connected_object);
    }
}

void Trigger::CheckPoint()
{
    auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();
    player_->GetComponentByTemplate<RigidBody>()->SetIsStopped(true);
    player_->GetComponentByTemplate<RigidBody>()->SetVelocity(0);
    m_connected_object->GetComponentByTemplate<Animation>()->SetIsActive(true);
    m_connected_object->SetDepth(GAME_OBJECT - 0.1f);
    if(m_connected_object->GetComponentByTemplate<Animation>()->IsDone())
    {
        isTriggered = false;
        object->GetComponentByTemplate<Trigger>()->GetConnectedObject()->SetDepth(GAME_OBJECT);
        player_->GetComponentByTemplate<RigidBody>()->SetIsStopped(false);
        for (auto player : Objectmanager_.GetObjectMap())
        {
            if (player.get()->GetObjectType() == ObjectType::Capture_Camera_main)
            {
                player.get()->GetComponentByTemplate<Capture>()->SetResetPosition(m_connected_object->GetTransform().GetTranslation());
            }
        }
        object->SetIsDead(true);
    }
}