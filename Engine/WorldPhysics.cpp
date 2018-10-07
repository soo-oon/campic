#include "WorldPhysics.h"
#include "PhysicsComponent.hpp"

void WorldPhysics::Movement(std::string object_name)
{
	vector2 object_velocity = object_manager.FindObject(object_name)->GetComponentByTemplate<Physics>()->GetVelocity();
}
