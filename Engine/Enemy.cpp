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

Enemy::Enemy(MoveType move_type)
{
	move_t = move_type;
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

void Enemy::StraightMove()
{
    if (object->GetComponentByTemplate<RigidBody>())
    {
        vector2 come = vector2(Objectmanager_.GetObjectMap()[0].get()->GetTransform().GetTranslation().x - object->GetTransform().GetTranslation().x,
            Objectmanager_.GetObjectMap()[0].get()->GetTransform().GetTranslation().y - object->GetTransform().GetTranslation().y);
        vector2 no_come = normalize(come);
        if (magnitude(come) < magnitude(object->GetTransform().GetScale()))
        {
            object->GetComponentByTemplate<RigidBody>()->SetVelocity(0);
        }
        else
            object->GetComponentByTemplate<RigidBody>()->SetVelocity(5 * no_come);
    }
}

void Enemy::AnglerMove()
{
    if(object->GetComponentByTemplate<RigidBody>())
    {
        if (abs(Objectmanager_.GetObjectMap()[0].get()->GetTransform().GetTranslation().x - object->GetTransform().GetTranslation().x) >
            abs(Objectmanager_.GetObjectMap()[0].get()->GetTransform().GetTranslation().y - object->GetTransform().GetTranslation().y))
        {
            if(Objectmanager_.GetObjectMap()[0].get()->GetTransform().GetTranslation().x - object->GetTransform().GetTranslation().x > 0)
                object->GetComponentByTemplate<RigidBody>()->SetVelocity({
                    object->GetComponentByTemplate<Status>()->GetSpeed() * 5 , 0 });
            else
                object->GetComponentByTemplate<RigidBody>()->SetVelocity({
                    object->GetComponentByTemplate<Status>()->GetSpeed() * -5 , 0 });
        }

        else
        {
            if(Objectmanager_.GetObjectMap()[0].get()->GetTransform().GetTranslation().y - object->GetTransform().GetTranslation().y > 0)
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
    Object* card = new Object();
    card->SetTranslation({ object->GetTransform().GetTranslation() });
    card->SetScale({ 24.f, 30.f });
    card->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    card->AddComponent(new Status(ObjectType::Item));
    card->AddComponent(new Collision(box_, { object->GetTransform().GetTranslation() }, { 24.f,30.f }));
    object->GetComponentByTemplate<Status>()->SetObjectType(ObjectType::Item);
    object->GetTransform().SetScale({ 24.f, 30.f });
    object->GetComponentByTemplate<Collision>()->ChangeCollisionBoxScale({ 24.f,30.f });
    int random = rand() % 4;
    if (random == 0)
    {
        card->AddComponent(new Sprite("asset/images/red_soul.png"));
        card->AddComponent(new Card("Red"));
    }
    else if (random == 1)
    {
        card->AddComponent(new Sprite("asset/images/blue_soul.png"));
        card->AddComponent(new Card("Blue"));
    }
    else if (random == 2)
    {
        card->AddComponent(new Sprite("asset/images/green_soul.png"));
        card->AddComponent(new Card("Green"));
    }
    else
    {
        card->AddComponent(new Sprite("asset/images/black_soul.png"));
        card->AddComponent(new Card("Black"));
    }
    Objectmanager_.AddObject(card);
}
