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