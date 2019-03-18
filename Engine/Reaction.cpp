/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Reaction.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jung Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Reaction.hpp"

void Reaction(Object* object, Object* di_object,float bounce)
{
	if (object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::stop)
	{
		StopReaction(object);
	}
        if (di_object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::stop)
        {
            StopReaction(di_object);
        }
	else if (object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::bounce)
	{
		BounceReaction(object);
	}
	else if(object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::none)
	{
	}
	if(object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::damaged)
	{
		if (object->GetComponentByTemplate<Collision>()->GetIsDamaged())
		{
			AttackedReaction(object, di_object); 
		}
		object->GetComponentByTemplate<Collision>()->Nohit();
	}
	else if (di_object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::damaged)
	{
		if (di_object->GetComponentByTemplate<Collision>()->GetIsDamaged())
		{
			AttackedReaction(di_object, object);
		}
		di_object->GetComponentByTemplate<Collision>()->Nohit();
	}
	if (object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::exit_)
	{
			DoorReaction(object);
	}
	if (di_object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::exit_)
	{
			DoorReaction(di_object);
	}
	else if (di_object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::bounce)
	{
		BounceReaction(di_object);
	}
	else if (di_object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::none)
	{
	}
}
void StopReaction(Object* object)
{
	object->GetComponentByTemplate<RigidBody>()->SetVelocity({object->GetComponentByTemplate<RigidBody>()->GetVelocity().x , 0});
        object->GetComponentByTemplate<Collision>()->SetIsGround(true);
        object->GetTransform().SetTranslation({
                object->GetComponentByTemplate<RigidBody>()->GetPreviousPosition().x,
                object->GetComponentByTemplate<RigidBody>()->GetPreviousPosition().y });
}
void BounceReaction(Object *object, float bounce)
{
	object->GetComponentByTemplate<RigidBody>()->SetVelocity(-vector2
		(abs(magnitude(object->GetComponentByTemplate<RigidBody>()->GetVelocity()))
		* normalize(object->GetComponentByTemplate<RigidBody>()->GetVelocity())) * bounce);
}

void AttackedReaction(Object* object , Object* di_object, float power)
{
	object->GetComponentByTemplate<RigidBody>()->SetVelocity(-vector2(
		power * normalize(vector2(di_object->GetTransform().GetTranslation().x - object->GetTransform().GetTranslation().x
			, di_object->GetTransform().GetTranslation().y - object->GetTransform().GetTranslation().y))));
	//di_object->GetComponentByTemplate<Collision>()->ToggleIsDamaged();
}

void DisappearReaction(Object * object)
{
}

void DoorReaction(Object * object)
{
	object->GetComponentByTemplate<Collision>()->ToggleIsDoor();
}

void CollReaction(Object* object, Object* di_object)
{
    vector2 velo1 = object->GetComponentByTemplate<RigidBody>()->GetVelocity();
    vector2 velo2 = di_object->GetComponentByTemplate<RigidBody>()->GetVelocity();
    if(magnitude(velo1) > magnitude(velo2))
    {
        object->GetComponentByTemplate<RigidBody>()->SetVelocity(velo1 - velo2);
        di_object->GetComponentByTemplate<RigidBody>()->AddVelocity(1.2f*(velo1 - velo2));
    }
    else
    {
        di_object->GetComponentByTemplate<RigidBody>()->SetVelocity(velo2 - velo1);
        object->GetComponentByTemplate<RigidBody>()->AddVelocity(1.2f*(velo2 - velo1));
    }
}
