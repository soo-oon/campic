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
    void SetMass(float mass) { m_inverse_mass = 1.f / mass; }
    void SetVelocity(vector2 velocity_) { m_velocity = velocity_; }
    void SetViewingDirection(vector2 direction) { m_viewing_direction = direction; }
    void SetJumping(bool rest) { isJumping = rest; }
    void SetGravity(float gravity_) { m_gravity = gravity_; }
public:
    vector2 GetPreviousPosition() { return m_previous_position; }
    vector2 GetVelocity() { return m_velocity; }
    vector2 GetPosition(){ return m_position; }
    vector2 GetViewingDirection() { return m_viewing_direction; }
    float GetGravity() { return m_gravity; }
    bool GetJumping() { return isJumping; }
    

private:
    vector2 m_previous_position;
    vector2 m_force_accumlator; // mess 
    vector2 m_velocity;
    vector2 m_position;
    vector2 m_viewing_direction;
    float m_friction = 0.99f;
    float m_gravity = 1.5f;
    float m_inverse_mass = 1;

    bool isJumping = false;
    bool collision_switch = false;

    Transform transform;
};
