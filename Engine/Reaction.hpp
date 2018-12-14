/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Reaction.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jung Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/


#pragma once
#include "Collision.hpp"
#include "RigidBody.hpp"

    void Reaction(Object* object, Object* di_object, float bounce = 1);
    void StopReaction(Object* object);
    void BounceReaction(Object* object, float bounce = 1);
    void AttackedReaction(Object* object, Object* di_object, float power = 50);
    void DisappearReaction(Object* object);
    void DoorReaction(Object* object);