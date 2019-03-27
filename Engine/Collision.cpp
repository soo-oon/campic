/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jung Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#include "Collision.hpp"
#include "Mesh.hpp"
#include "RigidBody.hpp"
#include <iostream>


bool Collision::Initialize(Object* Ob)
{
	if (object == nullptr)
	{
		object = Ob;

		collision_transform.SetTranslation(object->GetTransform().GetTranslation());
		collision_transform.SetScale(object->GetTransform().GetScale());
		collision_transform.SetRotation(object->GetTransform().GetRotation());
		collision_transform.SetDepth(object->GetTransform().GetDepth());
		collision_mesh = mesh::CreateCollisionBox(type);
	}
	return true;
}


void Collision::Update(float dt)
{
	if (object->GetTransform().GetParent() == nullptr)
	{
		collision_transform.SetTranslation(object->GetTransform().GetTranslation());
	}
	else
	{
		collision_transform.SetTranslation(object->GetTransform().GetParent()->GetTranslation());
	}

	if (restitution_ != RestitutionType::exit_)
		isdoor = false;
	if(GetJumpingitutionType() != RestitutionType::get)
	SetJumpingitutionType(RestitutionType::none);
}

void Collision::Delete()
{
}

void Collision::SetJumpingitutionType(RestitutionType restitution)
{
	restitution_ = restitution;
}

RestitutionType & Collision::GetJumpingitutionType()
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

void Collision::SetCollisionScale(vector2 size_)
{
	collision_transform.SetScale(size_);
}
