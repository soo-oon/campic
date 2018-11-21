#include "WorldPhysics.h"
#include "RigidBody.hpp"
#include "Input.hpp"
#include "Object.hpp"
#include "vector2.hpp"

void WorldPhysics::Movement(Object& object_name)
{
    vector2 object_velocity = object_name.GetComponentByTemplate<RigidBody>()->GetVelocity();
    object_name.GetTransform().SetTranslation(
        (object_name.GetTransform().GetTranslation().x + object_name
                                                         .GetComponentByTemplate<RigidBody>()->GetVelocity().x
            ,
            object_name.GetTransform().GetTranslation().y + object_name
                                                            .GetComponentByTemplate<RigidBody>()->
                                                            GetVelocity().y));
}

void WorldPhysics::Movement_by_key(Object& object_name)
{
	/*else if (Input::IsKeyAnyReleased())
	{
		object_name.GetComponentByTemplate<Physics>()->SetVelocity(vector2(0, 0));
	}*/
}

void WorldPhysics::Gravity_on(Objectmanager* objectmanager_, float gravity)
{
	for (std::map<std::string, std::unique_ptr<Object>>::iterator it = objectmanager_->GetObjectMap().begin(); it != objectmanager_->GetObjectMap().end(); ++it)
	{
		objectmanager_->FindObject((*it).first)->SetGravity(gravity);
	}
}

void WorldPhysics::Movement_Velocity(Object & object_name)
{
	if (Input::IsKeyPressed(GLFW_KEY_W))
	{
		object_name.GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(0, 5));
	}
	if (Input::IsKeyPressed(GLFW_KEY_A))
	{
		object_name.GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(-5, 0));
	}
	if (Input::IsKeyPressed(GLFW_KEY_S))
	{
		object_name.GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(0, -5));
	}
	if (Input::IsKeyPressed(GLFW_KEY_D))
	{
		object_name.GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(5, 0));
	}

}
