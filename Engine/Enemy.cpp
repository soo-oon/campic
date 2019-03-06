/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Enemy.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jung Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/


#include "Enemy.hpp"
#include "Status.hpp"
#include "Input.hpp"
#include "Card.hpp"
#include "Player.hpp"

Enemy::Enemy(MoveType move_type, Object* player)
{
	move_t = move_type;
        m_player = player;
}

bool Enemy::Initialize(Object * Ob)
{
	object = Ob;
	return false;
}

void Enemy::Update(float dt)
{
    MoveEnemy();
    if(!object->GetComponentByTemplate<Status>()->IsAlive())
    {
        CardDrop();
    }
    if (object->GetComponentByTemplate<Animation>()) {
        if (object->GetComponentByTemplate<RigidBody>()->GetVelocity().x < 0)
        {
            object->GetComponentByTemplate<Animation>()->ChangeAnimation("right", "left");
        }
        else
            object->GetComponentByTemplate<Animation>()->ChangeAnimation("left", "right");
    }

}

void Enemy::Delete()
{
}

void Enemy::MoveEnemy()
{
    switch (move_t)
    {
    case MoveType::straight:
        StraightMove();
    case MoveType::angler:
        AnglerMove();
    }
}
//
//void Enemy::Move(vector2 position)
//{
//    if (object->GetComponentByTemplate<RigidBody>())
//    {
//        vector2 come = vector2(position.x - object->GetTransform().GetTranslation().x,
//            position.y - object->GetTransform().GetTranslation().y);
//        vector2 n_come = normalize(come);
//        if (magnitude(come) < magnitude(object->GetTransform().GetScale()))
//        {
//            object->GetComponentByTemplate<RigidBody>()->SetVelocity(0);
//        }
//        else
//            object->GetComponentByTemplate<RigidBody>()->SetVelocity(5 * n_come);
//    }
//}

void Enemy::StraightMove()
{

        vector2 come = vector2(m_player->GetTransform().GetTranslation().x - object->GetTransform().GetTranslation().x,
            m_player->GetTransform().GetTranslation().y - object->GetTransform().GetTranslation().y);
        vector2 n_come = normalize(come);
        if (magnitude(come) < magnitude(object->GetTransform().GetScale()))
        {
            object->GetComponentByTemplate<RigidBody>()->SetVelocity(0);
        }
        else
            object->GetComponentByTemplate<RigidBody>()->SetVelocity(5 * n_come);
}

void Enemy::AnglerMove()
{
    if(object->GetComponentByTemplate<RigidBody>())
    {
        if (abs(m_player->GetTransform().GetTranslation().x - object->GetTransform().GetTranslation().x) >
            abs(m_player->GetTransform().GetTranslation().y - object->GetTransform().GetTranslation().y))
        {
            if(m_player->GetTransform().GetTranslation().x - object->GetTransform().GetTranslation().x > 0)
                object->GetComponentByTemplate<RigidBody>()->SetVelocity({
                    object->GetComponentByTemplate<Status>()->GetSpeed() * 5 , 0 });
            else
                object->GetComponentByTemplate<RigidBody>()->SetVelocity({
                    object->GetComponentByTemplate<Status>()->GetSpeed() * -5 , 0 });
        }

        else
        {
            if(m_player->GetTransform().GetTranslation().y - object->GetTransform().GetTranslation().y > 0)
                object->GetComponentByTemplate<RigidBody>()->SetVelocity({
                    0, object->GetComponentByTemplate<Status>()->GetSpeed() * 5 });
            else
                object->GetComponentByTemplate<RigidBody>()->SetVelocity({
                    0, object->GetComponentByTemplate<Status>()->GetSpeed() * -5 });
        }
    }
}

void Enemy::CardDrop()
{
    Object* soul = new Object();
    soul->SetTranslation({ object->GetTransform().GetTranslation() });
    soul->SetScale({ 24.f, 30.f });
    soul->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    soul->AddComponent(new Status(ObjectType::Item));
    soul->AddComponent(new Collision(box_));
    object->GetComponentByTemplate<Status>()->SetObjectType(ObjectType::Item);
    object->GetTransform().SetScale({ 24.f, 30.f });
    object->GetComponentByTemplate<Collision>()->ChangeCollisionBoxScale({ 24.f,30.f });
    int random = rand() % 4;
    if (random == 0)
    {
        soul->AddComponent(new Sprite("asset/images/red_soul.png"));
        soul->AddComponent(new Card("Red"));
    }
    else if (random == 1)
    {
        soul->AddComponent(new Sprite("asset/images/blue_soul.png"));
        soul->AddComponent(new Card("Blue"));
    }
    else if (random == 2)
    {
        soul->AddComponent(new Sprite("asset/images/green_soul.png"));
        soul->AddComponent(new Card("Green"));
    }
    else
    {
        soul->AddComponent(new Sprite("asset/images/black_soul.png"));
        soul->AddComponent(new Card("Black"));
    }
    Objectmanager_.AddObject(soul);
}
