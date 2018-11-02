#include "Collision.hpp"
#include <algorithm>
#include <iostream>
#include "Mesh.hpp"
#include "Physics.hpp"
#include "RigidBody.hpp"

bool Collision::Initialize(Object* Ob)
{
	object = Ob;
    collision_mesh = mesh::CreateCollisionBox(type,1, {255,0,0,255});

	return true;
}


void Collision::Update(float dt)
{
	collision_transform.SetTranslation(object->GetTransform().GetTranslation());
}

void Collision::Delete()
{
}

Mesh& Collision::GetCollsionMesh()
{
	return collision_mesh;
}

Transform& Collision::GetCollisionTransform()
{
	return collision_transform;
}

CollisionType & Collision::GetCollisionType()
{
	return type;
}

std::vector<vector2> Collision::GetCollisionCalculateTRS()
{
	std::vector<vector2> temp; 
	for (size_t i = 0; i < collision_mesh.GetCollisionVectors().size() - 2; i++)
		temp.emplace_back(collision_transform.GetTRS() * collision_mesh.GetCollisionVectors()[i] );
	return temp;
}
