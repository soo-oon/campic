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
#include "UI.hpp"

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
            capture_list.clear();
            collision_list.clear();
            projectile_list.clear();
            static_list.clear();
            dynamic_list.clear();
            for (auto obj = Objectmanager_.GetObjectMap().begin(); obj != Objectmanager_.GetObjectMap().end();)
            {
                if (auto temp = obj->get()->GetComponentByTemplate<Collision>(); temp != nullptr)
                {
                    if (temp->GetisGet())
                    {
                        obj = Objectmanager_.GetObjectMap().erase(obj);
                    }
                    else if (obj->get()->GetObjectType() == ObjectType::Player)
                    {
                        collision_list.push_back(obj->get());
                        ++obj;
                    }
                    else if (obj->get()->GetObjectType() == ObjectType::Item_Dynamic)
                    {
                        dynamic_list.push_back(obj->get());
                        ++obj;
                    }
                    else if (obj->get()->GetObjectType() == ObjectType::Item_Static)
                    {
                        static_list.push_back(obj->get());
                        ++obj;
                    }
                    else if (obj->get()->GetObjectType() == ObjectType::Projectile)
                    {
                        projectile_list.push_back(obj->get());
                        ++obj;
                    }
                    else if (obj->get()->GetObjectType() == ObjectType::Capture_Obj)
                    {
                        capture_list.push_back(obj->get());
                        ++obj;
                    }
                    else if (obj->get()->GetObjectType() == ObjectType::Door)
                    {
                        door = obj->get();
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
        if (collision_list.size() > 0)
        {
            for (int i = 0; i < collision_list.size(); i++)
            {
                auto p_collision = collision_list[i]->GetComponentByTemplate<Collision>();
                auto p_rigidbody = collision_list[i]->GetComponentByTemplate<RigidBody>();
                auto p_transform = collision_list[i]->GetTransform();
                tile_list.clear();
                ground_list.clear();
                TileCheck(collision_list[i]);
                GroundCheck(collision_list[i]);
                if (ground_list.size() > 0)
                {
                    for (auto ground : ground_list)
                    {
                        if (IntersectionCheckAABB(collision_list[i], ground))
                        {
                            StopReaction(collision_list[i], ground, true);
                        }
                    }
                }
                else
                    p_collision->SetIsGround(false);
                if (tile_list.size() > 0)
                {
                    for (auto tile : tile_list)
                    {
                        if(p_rigidbody->GetVelocity().y > 0)
                        {
                            if (IntersectionCheckAABB(collision_list[i], tile))
                            {
                                StopReaction(collision_list[i], tile, false);
                            }
                        }
                        if (p_rigidbody->GetVelocity().x != 0)
                        {
                            if (IntersectionCheckNextPosition(collision_list[i], tile))
                            {
                                p_rigidbody->SetVelocity
                                    ({0, p_rigidbody->GetVelocity().y});
                                if (p_transform.GetTranslation().x > tile->GetTransform().GetTranslation().x)
                                {
                                    p_collision->SetIsLeftTile(true);
                                }
                                else
                                {
                                    p_collision->SetIsRightTile(true);
                                }
                            }
                        }
                        if (IntersectionCheckAABBPositionLeft(collision_list[i], tile))
                        {
                            p_collision->SetIsLeftTile(true);
                            break;
                        }
                        p_collision->SetIsLeftTile(false);

                        if (IntersectionCheckAABBPositionRight(collision_list[i], tile))
                        {
                            p_collision->SetIsRightTile(true);
                            break;
                        }
                        p_collision->SetIsRightTile(false);
                    }
                }
                else
                {
                    p_collision->SetIsLeftTile(false);
                    p_collision->SetIsRightTile(false);
                }
                if (capture_list.size() > 0)
                {
                    for (auto capture : capture_list)
                    {
                        if (p_transform.GetTranslation().x - p_transform.GetScale().x / 2 - capture->GetTransform().GetScale().x / 2
                            <= capture->GetTransform().GetTranslation().x 
                            && capture->GetTransform().GetTranslation().x
                            <= p_transform.GetTranslation().x + p_transform.GetScale().x / 2 + capture->GetTransform().GetScale().x / 2
                            && p_transform.GetTranslation().y - p_transform.GetScale().y / 2 - capture->GetTransform().GetScale().y
                            <= capture->GetTransform().GetTranslation().y 
                            /*&& capture->GetTransform().GetTranslation().y
                            < p_transform.GetTranslation().y + p_transform.GetScale().y / 2 + capture
                                                                                              ->GetTransform().
                                                                                              GetScale().y*/)
                        {
                            if (capture->GetTransform().GetTranslation().y + capture->GetTransform().GetScale().y/2
                                + p_rigidbody->GetVelocity().y * dt
                                <= p_transform.GetTranslation().y - p_transform.GetScale().y / 2)
                            {
                                if (IntersectionCheckNextPosition(collision_list[i], capture))
                                {
                                    p_collision->SetIsCapobj(true);
                                    if(capture->GetComponentByTemplate<Collision>()->GetFilter() == Filter::Jump)
                                        p_rigidbody->SetYLimited(true);
                                    if (capture->GetComponentByTemplate<Collision>()->GetFilter() == Filter::Speed)
                                        p_rigidbody->SetXLimited(true);
                                    break;
                                }
                                if (capture->GetComponentByTemplate<Collision>()->GetFilter() == Filter::Speed)
                                    p_rigidbody->SetXLimited(false);
                                if (capture->GetComponentByTemplate<Collision>()->GetFilter() == Filter::Jump)
                                    p_rigidbody->SetYLimited(false);
                                p_collision->SetIsCapobj(false);
                            }
                            if(p_rigidbody->GetVelocity().y > 0)
                            {
                                    if (IntersectionCheckAABB(collision_list[i], capture))
                                    {
                                        StopReaction(collision_list[i], capture, false);
                                    }
                            }
                        }
                    }
                    for (auto capture : capture_list)
                    {
                        if (collision_list[i]->GetComponentByTemplate<RigidBody>()->GetVelocity().x != 0)
                        {
                            if (IntersectionCheckNextPosition(collision_list[i], capture))
                            {
                                p_rigidbody->SetVelocity
                                    ({0, p_rigidbody->GetVelocity().y});
                                if (p_transform.GetTranslation().x > capture->GetTransform().GetTranslation().x)
                                {
                                    p_collision->SetIsLeft(true);
                                }
                                else
                                {
                                    p_collision->SetIsRight(true);
                                }
                            }
                        }
                        if (IntersectionCheckAABBPositionRight(collision_list[i], capture))
                        {
                            p_rigidbody->SetVelocity
                                ({0, p_rigidbody->GetVelocity().y});
                            p_collision->SetIsRight(true);
                            break;
                        }
                        p_collision->SetIsRight(false);
                        if (IntersectionCheckAABBPositionLeft(collision_list[i], capture))
                        {
                            p_rigidbody->SetVelocity
                                ({0, p_rigidbody->GetVelocity().y});
                            p_collision->SetIsLeft(true);
                            break;
                        }
                        p_collision->SetIsLeft(false);
                    }
                }

				if (!dynamic_list.empty()) {
					for (auto dynamic_obj : dynamic_list)
					{
						if (auto collision = dynamic_obj->GetComponentByTemplate<Collision>();
							collision != nullptr)
						{
							if (IntersectionCheckAABB(collision_list[i], dynamic_obj))
							{
								collision->SetIsCollideItem(true);
							}
							else
							{
								collision->SetIsCollideItem(false);
							}
						}

					}
				}

                for (int j = 0; j < projectile_list.size(); j++)
                {
                    for (int k = j; k < projectile_list.size(); k++)
                    {
                        if (j != k)
                        {
                            if (IntersectionCheckAABB(projectile_list[j], projectile_list[k]))
                            {
                                projectile_list[k]->SetIsDead(true);
                                projectile_list[j]->SetIsDead(true);
                            }
                        }
                    }
                    if (IntersectionCheckAABB(collision_list[i], projectile_list[j]))
                    {
                        StopReaction(collision_list[i], projectile_list[j], false);
                    }
                    if (static_list.size() > 0)
                    {
                        for (auto statics : static_list)
                        {
                            if (IntersectionCheckAABB(statics, projectile_list[j]))
                            {
                                statics->SetIsDead(true);
                                projectile_list[j]->SetIsDead(true);
                            }
                        }
                    }
                }
                if (door)
                {
                    if (IntersectionCheckAABB(collision_list[i], door))
                    {
                        door->GetComponentByTemplate<UI>()->TriggerLevelLock(door->GetComponentByTemplate<UI>()->GetId());
                        StateManager_.GetCurrentState()->SetLevelIndicator(door->GetComponentByTemplate<UI>()->GetId());
                        StateManager_.GetCurrentState()->ChangeLevel(StateManager_.GetCurrentState()->GetLevelIndicator());
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
        object1.GetComponentByTemplate<Collision>()->SetJumpingitutionType(stop);
        object2.GetComponentByTemplate<Collision>()->SetJumpingitutionType(none);
    }

    //if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Wall)
    //{
    //    object1.GetComponentByTemplate<Collision>()->SetJumpingitutionType(stop);
    //    object2.GetComponentByTemplate<Collision>()->SetJumpingitutionType(none);
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Sword)
    //{
    //    if (object2.GetComponentByTemplate<Collision>()->GetIsDamaged())
    //    {
    //        object2.GetComponentByTemplate<Collision>()->SetJumpingitutionType(damaged);
    //        object1.GetComponentByTemplate<Status>()->Damaged(object1.GetComponentByTemplate<Status>()->GetDamage());
    //    }
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Sword
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy)
    //{
    //    if (object1.GetComponentByTemplate<Collision>()->GetIsDamaged())
    //    {
    //        object1.GetComponentByTemplate<Collision>()->SetJumpingitutionType(damaged);
    //        object2.GetComponentByTemplate<Status>()->Damaged(object1.GetComponentByTemplate<Status>()->GetDamage());
    //    }
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Shooting)
    //{
    //    object1.GetComponentByTemplate<Status>()->Damaged(object2.GetComponentByTemplate<Status>()->GetDamage());
    //    object2.GetComponentByTemplate<Collision>()->SetJumpingitutionType(get);
    //    previous_size -= 1;
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Shooting
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy)
    //{
    //    object2.GetComponentByTemplate<Status>()->Damaged(object2.GetComponentByTemplate<Status>()->GetDamage());
    //    object1.GetComponentByTemplate<Collision>()->SetJumpingitutionType(get);
    //    previous_size -= 1;
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Item)
    //{
    //    object2.GetComponentByTemplate<Collision>()->SetJumpingitutionType(get);
    //    previous_size -= 1;
    //    object1.GetComponentByTemplate<Player>()->SetCardList(object2.GetComponentByTemplate<Card>()->GetName());
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Item
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player)
    //{
    //    object1.GetComponentByTemplate<Collision>()->SetJumpingitutionType(get);
    //    previous_size -= 1;
    //    if (object1.GetComponentByTemplate<Card>() != nullptr)
    //        object2.GetComponentByTemplate<Player>()->SetCardList(object1.GetComponentByTemplate<Card>()->GetName());
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy)
    //{
    //    object1.GetComponentByTemplate<Collision>()->SetJumpingitutionType(stop);
    //    object2.GetComponentByTemplate<Collision>()->SetJumpingitutionType(stop);
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player)
    //{
    //    object2.GetComponentByTemplate<Collision>()->SetJumpingitutionType(bounce);
    //    object1.GetComponentByTemplate<Collision>()->SetJumpingitutionType(bounce);
    //    object2.GetComponentByTemplate<Status>()->Damaged(object1.GetComponentByTemplate<Status>()->GetDamage());
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Enemy)
    //{
    //    object1.GetComponentByTemplate<Collision>()->SetJumpingitutionType(bounce);
    //    object2.GetComponentByTemplate<Collision>()->SetJumpingitutionType(bounce);
    //    object1.GetComponentByTemplate<Status>()->Damaged(object2.GetComponentByTemplate<Status>()->GetDamage());
    //}
    //else if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Sword)
    //{
    //    object1.GetComponentByTemplate<Collision>()->SetJumpingitutionType(none);
    //    object2.GetComponentByTemplate<Collision>()->SetJumpingitutionType(none);
    //}
    //if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Door
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player)
    //{
    //    object1.GetComponentByTemplate<Collision>()->SetJumpingitutionType(exit_);
    //}
    //if (object1.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Player
    //    && object2.GetComponentByTemplate<Status>()->GetObjectType() == ObjectType::Door)
    //{
    //    object2.GetComponentByTemplate<Collision>()->SetJumpingitutionType(exit_);
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

bool Physics::IntersectionCheckAABB(Object* object1, Object* object2)
{
    std::vector<vector2> owner = object1->GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS();
    std::vector<vector2> object = object2->GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS();
    if (owner[0].x >= object[0].x && owner[0].x >= object[1].x)
        return false;
    if (owner[1].x <= object[0].x && owner[1].x <= object[1].x)
        return false;
    if (owner[1].y >= object[2].y && owner[1].y >= object[1].y)
        return false;
    if (owner[2].y <= object[2].y && owner[2].y <= object[1].y)
        return false;

    return true;
}

bool Physics::IntersectionCheckAABBPositionBase(Object* object1, Object* object2)
{
    //vector2 min_obj1 = {object2->GetTransform().GetTranslation().x - object2->GetTransform().GetScale()}
    vector2 min_obj = {
        object1->GetTransform().GetTranslation().x - object1->GetTransform().GetScale().x / 2,
        object1->GetTransform().GetTranslation().y - 2 - object1->GetTransform().GetScale().y / 2
    };
    vector2 max_obj = {
        object1->GetTransform().GetTranslation().x + object1->GetTransform().GetScale().x / 2,
        object1->GetTransform().GetTranslation().y - object1->GetTransform().GetScale().y / 2
    };

    vector2 min_pos = {
        object2->GetTransform().GetTranslation().x - object2->GetTransform().GetScale().x / 2,
        object2->GetTransform().GetTranslation().y - object2->GetTransform().GetScale().y / 2
    };
    vector2 max_pos = {
        object2->GetTransform().GetTranslation().x + object2->GetTransform().GetScale().x / 2,
        object2->GetTransform().GetTranslation().y + object2->GetTransform().GetScale().y / 2
    };

    if ((min_obj.x >= max_pos.x) || (max_obj.x <= min_pos.x) ||
        (min_obj.y >= max_pos.y) || (max_obj.y <= min_pos.y))
    {
        return false;
    }
    return true;
}

bool Physics::IntersectionCheckAABBPositionLeft(Object* object1, Object* object2)
{
    //vector2 min_obj1 = {object2->GetTransform().GetTranslation().x - object2->GetTransform().GetScale()}
    vector2 min_obj, max_obj, min_pos, max_pos;
    min_obj = {
        object1->GetTransform().GetTranslation().x - 3 - object1->GetTransform().GetScale().x / 2,
        object1->GetTransform().GetTranslation().y - object1->GetTransform().GetScale().y / 2
    };
    max_obj = {
        object1->GetTransform().GetTranslation().x - object1->GetTransform().GetScale().x / 2,
        object1->GetTransform().GetTranslation().y + object1->GetTransform().GetScale().y / 2
    };

    min_pos = {
        object2->GetTransform().GetTranslation().x - object2->GetTransform().GetScale().x / 2,
        object2->GetTransform().GetTranslation().y - object2->GetTransform().GetScale().y / 2
    };
    max_pos = {
        object2->GetTransform().GetTranslation().x + object2->GetTransform().GetScale().x / 2,
        object2->GetTransform().GetTranslation().y + object2->GetTransform().GetScale().y / 2
    };

    if ((min_obj.x >= max_pos.x) || (max_obj.x <= min_pos.x) ||
        (min_obj.y >= max_pos.y) || (max_obj.y <= min_pos.y))
    {
        return false;
    }
    return true;
}

bool Physics::IntersectionCheckAABBPositionRight(Object* object1, Object* object2)
{
    //vector2 min_obj1 = {object2->GetTransform().GetTranslation().x - object2->GetTransform().GetScale()}
    vector2 min_obj, max_obj, min_pos, max_pos;
    min_obj = {
        object1->GetTransform().GetTranslation().x + object1->GetTransform().GetScale().x / 2,
        object1->GetTransform().GetTranslation().y - object1->GetTransform().GetScale().y / 2
    };
    max_obj = {
        object1->GetTransform().GetTranslation().x + 3 + object1->GetTransform().GetScale().x / 2,
        object1->GetTransform().GetTranslation().y + object1->GetTransform().GetScale().y / 2
    };

    min_pos = {
        object2->GetTransform().GetTranslation().x - object2->GetTransform().GetScale().x / 2,
        object2->GetTransform().GetTranslation().y - object2->GetTransform().GetScale().y / 2
    };
    max_pos = {
        object2->GetTransform().GetTranslation().x + object2->GetTransform().GetScale().x / 2,
        object2->GetTransform().GetTranslation().y + object2->GetTransform().GetScale().y / 2
    };

    if ((min_obj.x >= max_pos.x) || (max_obj.x <= min_pos.x) ||
        (min_obj.y >= max_pos.y) || (max_obj.y <= min_pos.y))
    {
        return false;
    }
    return true;
}

bool Physics::IntersectionCheckNextPosition(Object* object1, Object* object2)
{
    vector2 min_obj, max_obj, min_pos, max_pos;
    min_obj = {
        object1->GetComponentByTemplate<RigidBody>()->GetNextPosition().x - object1->GetTransform().GetScale().x / 2,
        object1->GetComponentByTemplate<RigidBody>()->GetNextPosition().y - object1->GetTransform().GetScale().y / 2
    };
    max_obj = {
        object1->GetComponentByTemplate<RigidBody>()->GetNextPosition().x + object1->GetTransform().GetScale().x / 2,
        object1->GetComponentByTemplate<RigidBody>()->GetNextPosition().y + object1->GetTransform().GetScale().y / 2
    };

    min_pos = {
        object2->GetTransform().GetTranslation().x - object2->GetTransform().GetScale().x / 2,
        object2->GetTransform().GetTranslation().y - object2->GetTransform().GetScale().y / 2
    };
    max_pos = {
        object2->GetTransform().GetTranslation().x + object2->GetTransform().GetScale().x / 2,
        object2->GetTransform().GetTranslation().y + object2->GetTransform().GetScale().y / 2
    };

    if ((min_obj.x >= max_pos.x) || (max_obj.x <= min_pos.x) ||
        (min_obj.y >= max_pos.y) || (max_obj.y <= min_pos.y))
    {
        return false;
    }
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
