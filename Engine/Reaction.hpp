#pragma once
#pragma once
#include "Collision.hpp"
#include "RigidBody.hpp"

    void Reaction(Object* object, Object* di_object, float bounce = 1);
    void StopReaction(Object* object);
    void BounceReaction(Object* object, float bounce = 1);
    void AttackedReaction(Object* object, Object* di_object, float power = 100);
    void DisappearReaction(Object* object);