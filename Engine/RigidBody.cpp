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
#include "Player.hpp"
#include <iostream>

bool RigidBody::Initialize(Object* Ob)
{
	if (object == nullptr)
	{
		object = Ob;
		previous_position = object->GetTransform().GetTranslation();
		force_accumlator = { 0, 0 };
		velocity = { 0, 0 };
        viewing_direction = { 0,0 };
	}
        velocity = { 0, 0 };
    return true;
}

void RigidBody::Update(float dt)
{
    // for stop reaction
	previous_position = object->GetTransform().GetTranslation();

    // normalized velocity.
    viewing_direction = normalize(velocity);
    
	// calculate current velocity.
	velocity += inverse_mass * (force_accumlator * dt);
    
	// zero out accumulated force
	force_accumlator = {0, 0};

	//friction always activated
	//velocity *= friction;

	// integrate position
	if (magnitude(velocity) < 0.001f)
		velocity = 0;	
	
        // integrate position
        if (!object->GetComponentByTemplate<Collision>()->GetIsGround())
        {
            object->GetTransform().SetTranslation({ (object->GetTransform().GetTranslation().x + (velocity * dt).x),
                (object->GetTransform().GetTranslation().y + (velocity * dt).y) -gravity });
        }
        else
            object->GetTransform().SetTranslation({ (object->GetTransform().GetTranslation().x + (velocity * dt).x),
                (object->GetTransform().GetTranslation().y) });
}

void RigidBody::Delete()
{
}
