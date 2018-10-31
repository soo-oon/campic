#include "Collision.hpp"
#include <algorithm>
#include <iostream>
#include "Mesh.hpp"

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

bool Collision::collision_(vector2 Axis, std::vector<vector2> owner, std::vector<vector2> object)
{
	float minA, maxA;
	float minB, maxB;
	Interval(owner, Axis, minA, maxA);
	Interval(object, Axis, minB, maxB);

	float d0 = minA - maxB;
	float d1 = minB - maxA;

	if (d0 > 0.0f || d1 > 0.0f)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Collision::Interval(std::vector<vector2>vertices, vector2 Axis, float& min, float& max)
{
	min = max = dot(vertices[0], Axis);
	for (auto vertex : vertices)
	{
		float d = dot(vertex, Axis);
		if (d < min) min = d;
		else if (d > max) max = d;
	}
	//It should return projection of 2 polygon 
	//polygon should have min max value
	//It projection to axis of box
}

std::vector<vector2> Collision::line(std::vector<vector2> line_)
{
	std::vector<vector2> temp;
	if (line_.size() == 4)
	{
		temp.push_back(line_[0] - line_[1]);
		temp.push_back(line_[1] - line_[3]);
		temp.push_back(line_[3] - line_[2]);
		temp.push_back(line_[0] - line_[2]);
	}
	else
	{
		for (int i = 0; i < static_cast<int>(line_.size() - 1); i++)
		{
			temp.push_back(line_[i] - line_[i + 1]);
		}
		temp.push_back(line_[static_cast<int>(line_.size() - 1)] - line_[0]);
	}
	return temp;
}

bool Collision::intersection_check(std::vector<vector2> owner, std::vector<vector2> object)
{
	std::vector<vector2> axis;
	for (auto i : line(owner))
	{
		if (!collision_(vector2(-i.y, i.x), owner, object))
		{
			//std::cout << "No Intersec" << std::endl;
			return false;
		}
	}
	for (auto i : line(object))
	{
		axis.emplace_back(vector2(-i.y, i.x));
		if (!collision_(vector2(-i.y, i.x), owner, object))
		{
			//std::cout << "No Intersec" << std::endl;
			return false;
		}
	}
	//calculate axis of length.
	//take projection of other function.
	//and take min and max
	//if min
   // std::cout << "Yes, Intersection" << std::endl;
	return true;
}


