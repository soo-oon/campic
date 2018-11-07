#pragma once
#include "Collision.hpp"
#include "RigidBody.hpp"

void restitution(Object object)
{
    if(object.GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::stop)
    {
        object.GetTransform().SetTranslation({ 
            object.GetComponentByTemplate<RigidBody>()->GetPreviousPosition().x,
            object.GetComponentByTemplate<RigidBody>()->GetPreviousPosition().y });
        object.GetComponentByTemplate<RigidBody>()->SetVelocity(0);
    }
    else if(object.GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::bounce)
    {
        object.GetComponentByTemplate<RigidBody>()->SetVelocity(-vector2
        (abs(magnitude(object.GetComponentByTemplate<RigidBody>()->GetVelocity()))
            * normalize(object.GetComponentByTemplate<RigidBody>()->GetVelocity())));
    }
    else
    {
        
    }
}
