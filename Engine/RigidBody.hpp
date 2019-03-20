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
    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;
    void CollisionOn() { collision_switch = true; }
    void AddVelocity(vector2 velocity_) { m_velocity += velocity_; }
    void AddForce(vector2 force) { m_force_accumlator += force; }
public:
    void SetMass(float mass) { inverse_mass = 1.f / mass; }
    void SetVelocity(vector2 velocity_) { m_velocity = velocity_; }
    void SetViewingDirection(vector2 direction) { m_viewing_direction = direction; }
    void SetRest(bool rest) { isRest = rest; }
public:
    vector2 GetPreviousPosition() { return m_previous_position; }
    vector2 GetVelocity() { return m_velocity; }
    vector2 GetPosition(){ return m_position; }
    vector2 GetViewingDirection() { return m_viewing_direction; }
    bool GetRest() { return isRest; }
    

private:
    vector2 m_previous_position;
    vector2 m_force_accumlator; // mess 
    vector2 m_velocity;
    vector2 m_position;
    vector2 m_viewing_direction;
    float friction = 0.99f;
    float gravity = 1.f;
    float inverse_mass = 1;

    bool isRest = false;
    bool collision_switch = false;

    Transform transform;
};
