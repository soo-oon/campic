#include "WorldPhysics.h"
#include "PhysicsComponent.hpp"
#include "Input.hpp"
#include "Object.hpp"
#include "vector2.hpp"

void WorldPhysics::Movement(Object& object_name)
{
	vector2 object_velocity = object_name.GetComponentByTemplate<Physics>()->GetVelocity();
	object_name.GetTransform().SetTranslation((object_name.GetTransform().GetTranslation().x + object_name.GetComponentByTemplate<Physics>()->GetVelocity().x, 
		object_name.GetTransform().GetTranslation().y + object_name.GetComponentByTemplate<Physics>()->GetVelocity().y));
}
void WorldPhysics::Movement_by_key(Object& object_name)
{
	if(Input::IsKeyPressed(GLFW_KEY_UP))
	{
		object_name.GetComponentByTemplate<Physics>()->AddForce(vector2(0, 0.05));
	}
	else if (Input::IsKeyPressed(GLFW_KEY_LEFT))
	{
		object_name.GetComponentByTemplate<Physics>()->AddForce(vector2(-0.05, 0));
	}
	else	if (Input::IsKeyPressed(GLFW_KEY_DOWN))
	{
		object_name.GetComponentByTemplate<Physics>()->AddForce(vector2(0, -0.05));
	}
	else if (Input::IsKeyPressed(GLFW_KEY_RIGHT))
	{
		object_name.GetComponentByTemplate<Physics>()->AddForce(vector2(0.05, 0));
	}
	/*else if (Input::IsKeyAnyReleased())
	{
		object_name.GetComponentByTemplate<Physics>()->SetVelocity(vector2(0, 0));
	}*/
}
