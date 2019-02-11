/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: RigidBody.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jung Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "RigidBody.hpp"
#include "status.hpp"
#include "Player.hpp"
#include <iostream>


void RigidBody::CollisionOn()
{
    collision_switch = true;
}

void RigidBody::SetMass(float mass)
{
	inverse_mass = 1.f / mass;
}

void RigidBody::AddForce(vector2 force)
{
	force_accumlator += force;
}

void RigidBody::SetVelocity(vector2 velocity)
{
	this->velocity = velocity;
}

void RigidBody::AddVelocity(vector2 velocity)
{
	this->velocity += velocity;
}

vector2 RigidBody::GetPreviousPosition()
{
	return previous_position;
}

vector2 RigidBody::GetVelocity()
{
	return velocity;
}

vector2 RigidBody::GetPosition()
{
	return position;
}


bool RigidBody::Initialize(Object* Ob)
{
	if (object == nullptr)
	{
		object = Ob;
		previous_position = object->GetTransform().GetTranslation();
		force_accumlator = { 0, 0 };
		velocity = { 0, 0 };
	}
    return true;
}

void RigidBody::Update(float dt)
{
	previous_position = object->GetTransform().GetTranslation();

	gravity = 1 / object->GetGravity();
	// calculate current velocity.
	velocity += inverse_mass * (force_accumlator * dt);
	if(object->GetComponentByTemplate<Status>() != nullptr)
		velocity *=object->GetComponentByTemplate<Status>()->GetSpeed();

	// zero out accumulated force
	force_accumlator = {0, 0};

	//friction always activated
	//velocity *= friction;

	// integrate position
	if (magnitude(velocity) < 0.001f)
		velocity = 0;	
	
    // integrate position
	object->GetTransform().SetTranslation({ (object->GetTransform().GetTranslation().x + (gravity*velocity * dt).x), (object->GetTransform().GetTranslation().y + (gravity*velocity * dt).y) });
}

void RigidBody::Delete()
{
}
