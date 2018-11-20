#include "Collision.hpp"
#include "Mesh.hpp"
#include "RigidBody.hpp"

bool Collision::Initialize(Object* Ob)
{
	object = Ob;

    collision_mesh = mesh::CreateCollisionBox(type,150, {255,0,0,255});

	return true;
}


void Collision::Update(float dt)
{
	collision_transform.SetTranslation(object->GetTransform().GetTranslation());
}

void Collision::Delete()
{
}

void Collision::SetRestitutionType(RestitutionType restitution)
{
	restitution_ = restitution;
}

RestitutionType & Collision::GetRestitutionType()
{
    return restitution_;
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
	for (size_t i = 0; i < collision_mesh.GetCollisionVectors().size() - 1; i++)
		temp.emplace_back(collision_transform.GetTRS() * collision_mesh.GetCollisionVectors()[i] );
	return temp;
}
