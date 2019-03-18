/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Physics.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jung Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Physics.hpp"
#include "RigidBody.hpp"
#include "Collision.hpp"
#include "Player.hpp"
#include "Application.hpp"
#include "Graphics.hpp"

Physics Physics_;

bool Physics::Initialize()
{
    return true;
}

void Physics::Update(float dt)
{
    if (!Objectmanager_.GetObjectMap().empty())
    {
        if (Objectmanager_.GetObjectMap().size() != previous_size)
        {
            collision_list.clear();
            for (auto obj = Objectmanager_.GetObjectMap().begin(); obj != Objectmanager_.GetObjectMap().end();)
            {
                if (auto temp = obj->get()->GetComponentByTemplate<Collision>(); temp != nullptr )
                {
                    if (temp->GetisGet())
                    {
                        obj = Objectmanager_.GetObjectMap().erase(obj);
                    }
                    else if(obj->get()->GetObjectType() == ObjectType::Item_Dynamic || obj->get()->GetObjectType() == ObjectType::Player)
                    {
                        collision_list.push_back(obj->get());
                        ++obj;
                    }
                    else if (obj->get()->GetObjectType() == ObjectType::Item_Static || obj->get()->GetObjectType() == ObjectType::Wall)
                    {
                        static_list.push_back(obj->get());
                        ++obj;
                    }
                    else
                        ++obj;
                }
                else
                    ++obj;
            }
            previous_size = static_cast<int>(Objectmanager_.GetObjectMap().size());
        }
        tile_list.clear();
        for (auto obj = Objectmanager_.GetObjectMap().begin(); obj != Objectmanager_.GetObjectMap().end();obj++)
        {
            if(obj->get()->GetObjectType() == ObjectType::Player)
            {
                TileCheck(obj->get());
            }
        }
        if (collision_list.size() >= 1)
        {
            for(int i = 0; i < collision_list.size(); i ++)
            {
                for (auto tile : tile_list) {
                    if (IntersectionCheck_AABB(*collision_list[i], *tile))
                    {
                        StopReaction(collision_list[i]);
                    }
                }
                for(auto static_object : static_list)
                {
                    if (IntersectionCheck_AABB(*collision_list[i], *static_object))
                    {
                        StopReaction(collision_list[i]);
                    }
                }
                for(int j = i ; j < collision_list.size(); j ++)
                {
                    if(i != j)
                    {
                        if (IntersectionCheck_AABB(*collision_list[i], *collision_list[j]))
                        {
                            CollReaction(collision_list[i], collision_list[j]);
                        }
                    }
                }
            }

        }
    }

}


void Physics::Quit()
{
    //temp_obj = nullptr;
}

void Physics::ChangeRestitutionOfOjbect(Object object1, Object object2)
{
    if (object1.GetObjectType() == ObjectType::None
        && object2.GetObjectType() == ObjectType::Wall)
    {
        object1.GetComponentByTemplate<Collision>()->SetRestitutionType(stop);
        object2.GetComponentByTemplate<Collision>()->SetRestitutionType(none);
    }

    //if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Wall)
    //{
    //    object1.GetComponentByTemplate<Collision>()->SetRestitutionType(stop);
    //    object2.GetComponentByTemplate<Collision>()->SetRestitutionType(none);
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Sword)
    //{
    //    if (object2.GetComponentByTemplate<Collision>()->GetIsDamaged())
    //    {
    //        object2.GetComponentByTemplate<Collision>()->SetRestitutionType(damaged);
    //        object1.GetComponentByTemplate<Status>()->Damaged(object1.GetComponentByTemplate<Status>()->GetDamage());
    //    }
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Sword
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy)
    //{
    //    if (object1.GetComponentByTemplate<Collision>()->GetIsDamaged())
    //    {
    //        object1.GetComponentByTemplate<Collision>()->SetRestitutionType(damaged);
    //        object2.GetComponentByTemplate<Status>()->Damaged(object1.GetComponentByTemplate<Status>()->GetDamage());
    //    }
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Shooting)
    //{
    //    object1.GetComponentByTemplate<Status>()->Damaged(object2.GetComponentByTemplate<Status>()->GetDamage());
    //    object2.GetComponentByTemplate<Collision>()->SetRestitutionType(get);
    //    previous_size -= 1;
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Shooting
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy)
    //{
    //    object2.GetComponentByTemplate<Status>()->Damaged(object2.GetComponentByTemplate<Status>()->GetDamage());
    //    object1.GetComponentByTemplate<Collision>()->SetRestitutionType(get);
    //    previous_size -= 1;
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Item)
    //{
    //    object2.GetComponentByTemplate<Collision>()->SetRestitutionType(get);
    //    previous_size -= 1;
    //    object1.GetComponentByTemplate<Player>()->SetCardList(object2.GetComponentByTemplate<Card>()->GetName());
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Item
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player)
    //{
    //    object1.GetComponentByTemplate<Collision>()->SetRestitutionType(get);
    //    previous_size -= 1;
    //    if (object1.GetComponentByTemplate<Card>() != nullptr)
    //        object2.GetComponentByTemplate<Player>()->SetCardList(object1.GetComponentByTemplate<Card>()->GetName());
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy)
    //{
    //    object1.GetComponentByTemplate<Collision>()->SetRestitutionType(stop);
    //    object2.GetComponentByTemplate<Collision>()->SetRestitutionType(stop);
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player)
    //{
    //    object2.GetComponentByTemplate<Collision>()->SetRestitutionType(bounce);
    //    object1.GetComponentByTemplate<Collision>()->SetRestitutionType(bounce);
    //    object2.GetComponentByTemplate<Status>()->Damaged(object1.GetComponentByTemplate<Status>()->GetDamage());
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy)
    //{
    //    object1.GetComponentByTemplate<Collision>()->SetRestitutionType(bounce);
    //    object2.GetComponentByTemplate<Collision>()->SetRestitutionType(bounce);
    //    object1.GetComponentByTemplate<Status>()->Damaged(object2.GetComponentByTemplate<Status>()->GetDamage());
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Sword)
    //{
    //    object1.GetComponentByTemplate<Collision>()->SetRestitutionType(none);
    //    object2.GetComponentByTemplate<Collision>()->SetRestitutionType(none);
    //}
    //if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Door
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player)
    //{
    //    object1.GetComponentByTemplate<Collision>()->SetRestitutionType(exit_);
    //}
    //if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Door)
    //{
    //    object2.GetComponentByTemplate<Collision>()->SetRestitutionType(exit_);
    //}
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
    return true;
}

void Physics::Interval(std::vector<vector2> vertices, vector2 Axis, float& min, float& max)
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
    if (object.GetComponentByTemplate<Collision>()->GetCollisionType() == box_)
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

bool Physics::IntersectionCheck_AABB(Object object1, Object object2)
{
    std::vector<vector2> owner = object1.GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS();
    std::vector<vector2> object = object2.GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS();
    if (owner[0].x > object[0].x && owner[0].x > object[1].x)
        return false;
    if (owner[1].x < object[0].x && owner[1].x < object[1].x)
        return false;
    if (owner[1].y > object[2].y && owner[1].y > object[1].y)
        return false;
    if (owner[2].y < object[2].y && owner[2].y < object[1].y)
        return false;

    return true;
}


bool Physics::OutOfCheckBoundary(Object* object)
{
    auto size = Graphics_.GetDisplaySize();

    if (object->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetTranslation().x +
        object->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale().x / 2 < size.x / 2 &&
        object->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetTranslation().x -
        object->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale().x / 2 > -size.x / 2 &&
        object->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetTranslation().y +
        object->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale().y / 2 < size.y / 2 &&
        object->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetTranslation().y -
        object->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale().y / 2 > -size.y / 2)
    {
        return false;
    }
    return true;
}
