#include "Collision.hpp"
#include "Mesh.hpp"
#include "RigidBody.hpp"
#include <iostream>


bool Collision::Initialize(Object* Ob)
{

	object = Ob;

	collision_mesh = mesh::CreateCollisionBox(type);

	return true;
}


void Collision::Update(float dt)
{
	collision_transform.SetTranslation(object->GetTransform().GetTranslation());
	if (restitution_ != RestitutionType::exit_)
		isdoor = false;
	if(GetRestitutionType() != RestitutionType::get)
	SetRestitutionType(RestitutionType::none);
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

void Collision::Compute_AABB(Mesh mesh, int num_point)
{
	vector2 maxpos = mesh.GetPoint(0) , minpos = mesh.GetPoint(0);;

	for (int i = 1; i < mesh.GetPointCount(); i++)
	{
		if (maxpos.x < mesh.GetPoint(i).x)
			maxpos.x = mesh.GetPoint(i).x;

		if (minpos.x > mesh.GetPoint(i).x)
			minpos.x = mesh.GetPoint(i).x;

		if (maxpos.y < mesh.GetPoint(i).y)
			maxpos.y = mesh.GetPoint(i).y;

		if (minpos.y > mesh.GetPoint(i).y)
			minpos.y = mesh.GetPoint(i).y;
	}
	height = (maxpos.y + minpos.y) / 2;
	width = (minpos.x + maxpos.x) / 2;

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

void Collision::ToggleIsDamaged()
{
	//if(isdamaged == false)
	//{
		isdamaged = true;
	//}
	//else
	//isdamaged = false;
}

bool Collision::GetIsDamaged()
{
	return isdamaged;
}

void Collision::Nohit()
{
	isdamaged = false;
}

void Collision::ToggleIsDoor()
{
	if (isdoor == false)
	{
		isdoor = true;
	}
}

bool Collision::GetIsDoor()
{
	return isdoor;
}

void Collision::SetIsDoorClose()
{
	isdoor = false;
}
