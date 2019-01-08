/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: RigidBody.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jung Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/


#pragma once
#include "Component.hpp"
#include "Transform.hpp"
#include "Object.hpp"
#include "StateManager.hpp"
#include "vector2.hpp"

class RigidBody : public Component
{
public:
    void CollisionOn();
    void SetMass(float mass);
    void SetVelocity(vector2 velocity);
    void AddVelocity(vector2 velocity);
    vector2 GetPreviousPosition();
    vector2 GetVelocity();
    vector2 GetPosition();
    void AddForce(vector2 force);
    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;
private:
    vector2 previous_position;
    vector2 force_accumlator; // mess 
    vector2 velocity;
    vector2 position;
    float friction = 0.99f;
    float gravity = 1;
    float inverse_mass = 1;

    bool collision_switch = false;

    Transform transform;
};
