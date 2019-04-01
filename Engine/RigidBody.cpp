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
            m_next_position = { 0,0 };
            isJumping = false;
            if (object->GetObjectType() == ObjectType::Player)
                isPlayer = true;
	}
        m_velocity = { 0, 0 };
    return true;
}

void RigidBody::Update(float dt)
{
    if (isPlayer)
    {
        MovePlayer();
    
    if(m_velocity.x > 200)
        m_velocity.x = 200;
	if (m_velocity.x < -200)
		m_velocity.x = -200;
    if (m_velocity.y > 200)
        m_velocity.y = 200;
    if (m_velocity.y < -200)
        m_velocity.y = -200;
	}
        // for stop reaction
	m_previous_position = object->GetTransform().GetTranslation();

        // normalized velocity.
        m_viewing_direction = normalize(m_velocity);
    
	// calculate current velocity.
	m_velocity += m_inverse_mass * (m_force_accumlator * dt);
    
	// zero out accumulated force
	m_force_accumlator = {0, 0};

	//m_friction always activated
	//m_velocity *= m_friction;
        m_velocity.y -= m_gravity;

	// integrate position
	if (magnitude(m_velocity) < 0.001f)
		m_velocity = 0;	
        // integrate position                   
            if (!object->GetComponentByTemplate<Collision>()->GetIsGround() && !object->GetComponentByTemplate<Collision>()->GetIsCapobj())
            {
                object->GetTransform().SetTranslation({ (object->GetTransform().GetTranslation().x + (m_velocity * dt).x),
                    (object->GetTransform().GetTranslation().y + (m_velocity* dt).y) });
            }
            else
            {
                object->GetTransform().SetTranslation({ (object->GetTransform().GetTranslation().x + (m_velocity * dt).x),
                    (object->GetTransform().GetTranslation().y) });
                isJumping = false;
            }
        if (!object->GetComponentByTemplate<Collision>()->GetIsGround())
            m_next_position = { (object->GetTransform().GetTranslation().x + (m_velocity * dt).x),
                    (object->GetTransform().GetTranslation().y + (m_velocity* dt).y) };
        else
            m_next_position = { (object->GetTransform().GetTranslation().x + (m_velocity * dt).x),
                (object->GetTransform().GetTranslation().y) };
/*
    if (isMoving) {
        if (!object->GetComponentByTemplate<Collision>()->GetIsGround() && !object->GetComponentByTemplate<Collision>()->GetIsCapobj())
        {
            object->GetTransform().SetTranslation({ (object->GetTransform().GetTranslation().x + (m_velocity * dt).x),
                (object->GetTransform().GetTranslation().y + (m_velocity* dt).y) });
        }
        else
        {
            object->GetTransform().SetTranslation({ (object->GetTransform().GetTranslation().x + (m_velocity * dt).x),
                (object->GetTransform().GetTranslation().y) });
            isJumping = false;
        }
    }
    if (!object->GetComponentByTemplate<Collision>()->GetIsGround())
        m_next_position = { (object->GetTransform().GetTranslation().x + (m_velocity * dt).x),
                (object->GetTransform().GetTranslation().y + (m_velocity* dt).y) };
    else
        m_next_position = { (object->GetTransform().GetTranslation().x + (m_velocity * dt).x),
            (object->GetTransform().GetTranslation().y) };
    if (isPlayer)
        MovePlayer();
        */
}

void RigidBody::Delete()
{
}

void RigidBody::MovePlayer()
{
    if (!object->GetComponentByTemplate<Collision>()->GetIsRight() && object->GetComponentByTemplate<Collision>()->GetIsLeft()
        || (!object->GetComponentByTemplate<Collision>()->GetIsRightTile() && object->GetComponentByTemplate<Collision>()->GetIsLeftTile()))
    {
        if (Input::IsKeyPressed(GLFW_KEY_D))
        {
            object->GetComponentByTemplate<Animation>()->SetFlip(false);
            object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 200, 
                object->GetComponentByTemplate<RigidBody>()->GetVelocity().y });
            key_press_d = true;
        }
        if (Input::IsKeyPressed(GLFW_KEY_A))
        {
            object->GetComponentByTemplate<Animation>()->SetFlip(true);
            object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0,
                object->GetComponentByTemplate<RigidBody>()->GetVelocity().y });
            key_press_a = true;
        }
        if (object->GetComponentByTemplate<RigidBody>()->GetJumping() == false)
        {
            if (Input::IsKeyTriggered(GLFW_KEY_W))
            {
                object->GetComponentByTemplate<Collision>()->SetIsGround(false);
                object->GetComponentByTemplate<Collision>()->SetIsCapobj(false);
                object->GetComponentByTemplate<RigidBody>()->SetVelocity(
                    { object->GetComponentByTemplate<RigidBody>()->GetVelocity().x,200 });
                object->GetComponentByTemplate<RigidBody>()->SetJumping(true);
            }
        }
    }
    else if (object->GetComponentByTemplate<Collision>()->GetIsRight() && !object->GetComponentByTemplate<Collision>()->GetIsLeft()
        || (object->GetComponentByTemplate<Collision>()->GetIsRightTile() && !object->GetComponentByTemplate<Collision>()->GetIsLeftTile()))
    {
        if (Input::IsKeyPressed(GLFW_KEY_D))
        {
            object->GetComponentByTemplate<Animation>()->SetFlip(false);
            object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0,
                object->GetComponentByTemplate<RigidBody>()->GetVelocity().y }); 
            key_press_d = true;
        }
        if (Input::IsKeyPressed(GLFW_KEY_A))
        {
            object->GetComponentByTemplate<Animation>()->SetFlip(true);
            object->GetComponentByTemplate<RigidBody>()->SetVelocity({ -200,
                object->GetComponentByTemplate<RigidBody>()->GetVelocity().y });
            key_press_a = true;
        }
        if (object->GetComponentByTemplate<RigidBody>()->GetJumping() == false)
        {
            if (Input::IsKeyTriggered(GLFW_KEY_W))
            {
                object->GetComponentByTemplate<Collision>()->SetIsGround(false);
                object->GetComponentByTemplate<Collision>()->SetIsCapobj(false); 
                object->GetComponentByTemplate<Collision>()->SetIsRightTile(true);
                object->GetComponentByTemplate<RigidBody>()->SetVelocity(
                    { 0,150 });
                object->GetComponentByTemplate<RigidBody>()->SetJumping(true);
            }
        }
    }
    else if ((!object->GetComponentByTemplate<Collision>()->GetIsRight() && !object->GetComponentByTemplate<Collision>()->GetIsLeft())
        && (!object->GetComponentByTemplate<Collision>()->GetIsRightTile() && !object->GetComponentByTemplate<Collision>()->GetIsLeftTile()))
    {
        if (Input::IsKeyPressed(GLFW_KEY_D))
        {
            object->GetComponentByTemplate<Animation>()->SetFlip(false);
            object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 200, 
                object->GetComponentByTemplate<RigidBody>()->GetVelocity().y });
            key_press_d = true;
        }
        if (Input::IsKeyPressed(GLFW_KEY_A))
        {
            object->GetComponentByTemplate<Animation>()->SetFlip(true);
            object->GetComponentByTemplate<RigidBody>()->SetVelocity({ -200,
                object->GetComponentByTemplate<RigidBody>()->GetVelocity().y });
            key_press_a = true;
        }
        if (object->GetComponentByTemplate<RigidBody>()->GetJumping() == false)
        {
            if (Input::IsKeyTriggered(GLFW_KEY_W))
            {
                object->GetComponentByTemplate<Collision>()->SetIsGround(false);
                object->GetComponentByTemplate<Collision>()->SetIsCapobj(false);
                object->GetComponentByTemplate<RigidBody>()->SetVelocity(
                    { object->GetComponentByTemplate<RigidBody>()->GetVelocity().x,200 });
                object->GetComponentByTemplate<RigidBody>()->SetJumping(true);
            }
        }
    }
    //else if (object->GetComponentByTemplate<Collision>()->GetIsRight() && object->GetComponentByTemplate<Collision>()->GetIsLeft()
    //    || (object->GetComponentByTemplate<Collision>()->GetIsRightTile() && object->GetComponentByTemplate<Collision>()->GetIsLeftTile()))
    //{
    //    if (Input::IsKeyPressed(GLFW_KEY_D))
    //    {
    //        object->GetComponentByTemplate<Animation>()->SetFlip(false);
    //        object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0,
    //            object->GetComponentByTemplate<RigidBody>()->GetVelocity().y });
    //        key_press_d = true;
    //    }
    //    if (Input::IsKeyPressed(GLFW_KEY_A))
    //    {
    //        object->GetComponentByTemplate<Animation>()->SetFlip(true);
    //        object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0,
    //            object->GetComponentByTemplate<RigidBody>()->GetVelocity().y });
    //        key_press_a = true;
    //    }
    //    if (object->GetComponentByTemplate<RigidBody>()->GetJumping() == false)
    //    {
    //        if (Input::IsKeyTriggered(GLFW_KEY_W))
    //        {
    //            object->GetComponentByTemplate<Collision>()->SetIsGround(false);
    //            object->GetComponentByTemplate<Collision>()->SetIsCapobj(false);
    //            object->GetComponentByTemplate<RigidBody>()->SetVelocity(
    //                { object->GetComponentByTemplate<RigidBody>()->GetVelocity().x,150 });
    //            object->GetComponentByTemplate<RigidBody>()->SetJumping(true);
    //        }
    //    }
    //}
    if (Input::IsKeyTriggered(GLFW_KEY_S))
    {
        object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0, -50 });
    }
    if (Input::IsKeyReleased(GLFW_KEY_A) )
        key_press_a = false;
    if (Input::IsKeyReleased(GLFW_KEY_D))
        key_press_d = false;
        if(!key_press_a && !key_press_d)
    {
        object->GetComponentByTemplate<RigidBody>()->SetVelocity(object->GetComponentByTemplate<RigidBody>()->GetVelocity()*m_friction);
    }
}
