#include "Reaction.hpp"

void Reaction(Object* object, Object* di_object,float bounce)
{
	if (object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::stop)
	{
		StopReaction(object);
	}
	else if (object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::bounce)
	{
		BounceReaction(object);
	}
	else if(object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::none)
	{

	}
	else if(object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::damaged)
	{
		if(di_object->GetComponentByTemplate<Collision>()->GetIsDamaged())
		AttackedReaction(object, di_object);
	}
	else if (object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::exit)
	{
		if (di_object->GetComponentByTemplate<Collision>()->GetIsDoor())
			DoorReaction(object);
	}
	if (di_object->GetComponentByTemplate<Collision>()->GetRestitutionType() == RestitutionType::stop)
	{
		StopReaction(di_object);
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
	object->GetTransform().SetTranslation({
		object->GetComponentByTemplate<RigidBody>()->GetPreviousPosition().x,
		object->GetComponentByTemplate<RigidBody>()->GetPreviousPosition().y });
	object->GetComponentByTemplate<RigidBody>()->SetVelocity(0);
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
	di_object->GetComponentByTemplate<Collision>()->ToggleIsDamaged();
}

void DisappearReaction(Object * object)
{
}

void DoorReaction(Object * object)
{
	object->GetComponentByTemplate<Collision>()->ToggleIsDoor();
}
