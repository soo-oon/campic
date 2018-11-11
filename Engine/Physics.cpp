#include "Physics.hpp"
#include "RigidBody.hpp"
#include "Collision.hpp"
#include "Character.hpp"

bool Physics::Initialize()
{
	return true;
}

void Physics::PhysicsObjectUpdate(Objectmanager* objectmanager)
{
	temp_obj = objectmanager;
}

void Physics::Update(float dt)
{
	collision_list.clear();
	if (temp_obj != nullptr)
	{
		for (std::map<std::string, std::unique_ptr<Object>>::iterator it = temp_obj->GetObjectMap().begin();
			it != temp_obj->GetObjectMap().end(); ++it)
		{
			Object* temp = (it->second.get());

			if (temp->GetComponentByTemplate<Collision>() != nullptr)
			{
				collision_list.push_back(temp);
				temp->GetComponentByTemplate<Collision>()->Update(dt);
			}
		}
	}
	if (collision_list.size() > 1)
	{
		for (size_t i = 0; i < collision_list.size() ; i++)
		{
			for (size_t j = i+1; j < collision_list.size(); j++)
			{
				if (i != j)
				{
					if(IntersectionCheck(*collision_list[i], *collision_list[j]))
					{
						ChangeRestitutionOfOjbect(*collision_list[i], *collision_list[j]);
						Reaction(collision_list[i], collision_list[j]);
					}
				}
			}
		}
	}
	if (temp_obj != nullptr)
	{
		for (std::map<std::string, std::unique_ptr<Object>>::iterator it = temp_obj->GetObjectMap().begin();
			it != temp_obj->GetObjectMap().end(); ++it)
		{
			Object temp = *(it->second.get());

			if (temp.GetComponentByTemplate<RigidBody>() != nullptr)
			{
				temp.GetComponentByTemplate<RigidBody>()->Update(dt);
			}
		}
	}
}


void Physics::Quit()
{
	temp_obj = nullptr;
}

void Physics::ChangeRestitutionOfOjbect(Object object1, Object object2)
{
	if(object1.GetComponentByTemplate<Character>()->GetCharType() == ObjectType::player 
		&& object2.GetComponentByTemplate<Character>()->GetCharType() == ObjectType::opponent)
	{
		object1.GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::bounce);
	}
	else if (object1.GetComponentByTemplate<Character>()->GetCharType() == ObjectType::player
		&& object2.GetComponentByTemplate<Character>()->GetCharType() == ObjectType::wall)
	{
		object1.GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::stop);
		object2.GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
	}
	else if (object1.GetComponentByTemplate<Character>()->GetCharType() == ObjectType::player
		&& object2.GetComponentByTemplate<Character>()->GetCharType() == ObjectType::sword)
	{
		object1.GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
		object2.GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
	}
	else if (object1.GetComponentByTemplate<Character>()->GetCharType() == ObjectType::opponent
		&& object2.GetComponentByTemplate<Character>()->GetCharType() == ObjectType::sword)
	{	
		if (object2.GetComponentByTemplate<Collision>()->GetIsDamaged())
		{
			object1.GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::damaged);
		}
	}
}


bool Physics::CollisionOnAxis(vector2 Axis, std::vector<vector2> owner, std::vector<vector2> object)
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

void Physics::Interval(std::vector<vector2>vertices, vector2 Axis, float& min, float& max)
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

std::vector<vector2> Physics::VectorToLine(Object object)
{
	std::vector<vector2> object_line;
	if(object.GetComponentByTemplate<Collision>()->GetCollisionType() == box_)
	{
		object_line.emplace_back(object.GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[0]
								- object.GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[1]);
		object_line.emplace_back(object.GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[2]
								- object.GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[1]);
		object_line.emplace_back(object.GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[3]
								- object.GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[2]);
		object_line.emplace_back(object.GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[0]
								- object.GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[3]);
	}
	return object_line;
	//std::vector<vector2> temp;
	//if (line_.size() == 4)
	//{
	//	temp.push_back(line_[0] - line_[1]);
	//	temp.push_back(line_[1] - line_[3]);
	//	temp.push_back(line_[3] - line_[2]);
	//	temp.push_back(line_[0] - line_[2]);
	//}
	//else
	//{
	//	for (int i = 0; i < static_cast<int>(line_.size() - 1); i++)
	//	{
	//		temp.push_back(line_[i] - line_[i + 1]);
	//	}
	//	temp.push_back(line_[static_cast<int>(line_.size() - 1)] - line_[0]);
	//}
	//return temp;
}
// should change take object.
bool Physics::IntersectionCheck(Object object1, Object object2)
{
	std::vector<vector2> owner = object1.GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS();
	std::vector<vector2> object = object2.GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS();
	std::vector<vector2> axis;
	for (auto i : VectorToLine(object1))
	{
		if (!CollisionOnAxis(vector2(-i.y, i.x), owner, object))
		{
			//std::cout << "No Intersec" << std::endl;
			return false;
		}
	}
	for (auto i : VectorToLine(object2))
	{
		axis.emplace_back(vector2(-i.y, i.x));
		if (!CollisionOnAxis(vector2(-i.y, i.x), owner, object))
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

void Physics::AddCollisionList(Object * object)
{
    object->GetTransform().GetTranslation();
}


