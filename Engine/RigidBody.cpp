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
#include "Input.hpp"

bool RigidBody::Initialize(Object* Ob)
{
	if (object == nullptr)
	{
	    object = Ob;
	    m_previous_position = object->GetTransform().GetTranslation();
	    m_force_accumlator = { 0, 0 };
	    m_velocity = { 0, 0 };
            m_viewing_direction = { 0,0 };
            isRest = false;
	}
        m_velocity = { 0, 0 };
    return true;
}

void RigidBody::Update(float dt)
{
    if(m_velocity.x > 100)
        m_velocity.x = 100;
	if (m_velocity.x < -100)
		m_velocity.x = -100;
    if (m_velocity.y > 100)
        m_velocity.y = 100;
    if (m_velocity.y < -100)
        m_velocity.y = -100;
        // for stop reaction
	m_previous_position = object->GetTransform().GetTranslation();

        // normalized velocity.
        m_viewing_direction = normalize(m_velocity);
    
	// calculate current velocity.
	m_velocity += inverse_mass * (m_force_accumlator * dt);
    
	// zero out accumulated force
	m_force_accumlator = {0, 0};

	//friction always activated
	//velocity *= friction;
        m_velocity.y -= gravity;

	// integrate position
	if (magnitude(m_velocity) < 0.001f)
		m_velocity = 0;	
        // integrate position
        if (!object->GetComponentByTemplate<Collision>()->GetIsGround())
        {
            object->GetTransform().SetTranslation({ (object->GetTransform().GetTranslation().x + (m_velocity * dt).x),
                (object->GetTransform().GetTranslation().y + (m_velocity* dt).y)});

            std::cout << object->GetComponentByTemplate<RigidBody>()->GetVelocity().x << ", "
                << object->GetComponentByTemplate<RigidBody>()->GetVelocity().y << std::endl;
        }
        else
        {
            object->GetTransform().SetTranslation({ (object->GetTransform().GetTranslation().x + (m_velocity * dt).x),
                (object->GetTransform().GetTranslation().y) });
            isRest = false;
        }
}

void RigidBody::Delete()
{
}
