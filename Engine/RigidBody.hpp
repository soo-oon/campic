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
	RigidBody()
	{
		type = Component_Type::RigidBody;
	}

    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;
    void CollisionOn() { collision_switch = true; }
    void AddVelocity(vector2 velocity_) { velocity += velocity_; }
    void AddForce(vector2 force) { force_accumlator += force; }
public:
    void SetMass(float mass) { inverse_mass = 1.f / mass; }
    void SetVelocity(vector2 velocity_) { velocity = velocity_; }
    void SetViewingDirection(vector2 direction) { viewing_direction = direction; }
public:
    vector2 GetPreviousPosition() { return previous_position; }
    vector2 GetVelocity() { return velocity; }
    vector2 GetPosition(){ return position; }
    vector2 GetViewingDirection() { return viewing_direction; }
    

private:
    vector2 previous_position;
    vector2 force_accumlator; // mess 
    vector2 velocity;
    vector2 position;
    vector2 viewing_direction;
    float friction = 0.99f;
    float gravity = 0.5f;
    float inverse_mass = 1;

    bool collision_switch = false;

    Transform transform;
};
