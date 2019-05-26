/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Physics.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Jung Soon Woo
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "Objectmanager.hpp"
#include "Collision.hpp"
#include "Reaction.hpp"
#include "Tile_Map.hpp"

class Physics
{
public:
	bool Initialize();
	void Update(float dt);

	//void PhysicsObjectUpdate(Objectmanager* objectmanager);

	void Quit();

	void ChangeRestitutionOfOjbect(Object object1, Object object2);

    void Restitution(Object* object1, Object* object2);

	// This function is used by intersection check. You do not use it for collision check.
	bool CollisionOnAxis(vector2 Axis, std::vector<vector2> owner, std::vector<vector2> object);
	// This function is used by upper function (CollisionOnAxis). It take interval between vertices. 
	void Interval(std::vector<vector2>vertices, vector2 Axis, float& min, float& max);
	// This function convert vector to line.
	std::vector<vector2> VectorToLine(Object object);
	// This is real intersection check which you use.
	bool IntersectionCheck(Object object1, Object object2);
        // This is intersection check which is AABB version for thin 
        bool IntersectionCheckAABB(Object* object1, Object* object2);
        bool IntersectionCheckAABBCenterPosition(Object* object1, Object* object2);
        bool IntersectionCheckAABBPositionBase(Object* object1, Object* object2);
        bool IntersectionCheckAABBPositionLeft(Object* object1, Object* object2);
        bool IntersectionCheckAABBPositionRight(Object* object1, Object* object2);
        bool IntersectionCheckNextPosition(Object* object1, Object* object2);
        bool IntersectionCheckAABBUpperCase(Object* object1, Object* object2);
        
	void ResetPreviousSize() { previous_size = 0; }

        // This function return true if object is out of window area. 
        bool OutOfCheckBoundary(Object* object);


    bool TransparentCheck(Object* object)
    {
        float value = dot(vector2(0, 1), object->GetComponentByTemplate<RigidBody>()->GetViewingDirection());
        if (value > 0)
        {
            return true;
        }
        else
            return false;
    }

    void TileCheck(Object* object)
    {
        float x_0 = object->GetTransform().GetTranslation().x;
        float y_0 = object->GetTransform().GetTranslation().y;
        float x_1 = object->GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[1].x;
        float x_2 = object->GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[0].x;
        float y_1 = object->GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[2].y;
        float y_2 = object->GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[1].y;
        if(object->GetComponentByTemplate<RigidBody>()->GetViewingDirection().x > 0)
        {
            if(object->GetComponentByTemplate<RigidBody>()->GetViewingDirection().y > 0)
            {
                if(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE/2, y_1 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE/2, y_1 }));
                if (Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_2 }));
                if (Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE/2, y_0 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE/2, y_0 }));
                if (Tile_Map_.GetSpecificTile({ x_1 , y_1 + TILE_SIZE/2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 , y_1 +TILE_SIZE/2 }));
                if (Tile_Map_.GetSpecificTile({ x_2 , y_1 + TILE_SIZE/2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_2 , y_1 +TILE_SIZE/2 }));
                if (Tile_Map_.GetSpecificTile({ x_0 , y_1 + TILE_SIZE / 2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_0 , y_1 + TILE_SIZE / 2 }));
                if (Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE / 2, y_1 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE / 2, y_1 }));
                if (Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE / 2, y_2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE / 2, y_2 }));
                if (Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE / 2, y_0 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE / 2, y_0 }));
            }
            else
            {
                if(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE/2, y_1 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE/2, y_1 }));
                if(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE/2, y_2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE/2, y_2 }));
                if(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE/2, y_0 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE/2, y_0 }));
                if(Tile_Map_.GetSpecificTile({ x_0 , y_2 - TILE_SIZE/2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_0 , y_2 - TILE_SIZE/2 }));
                if(Tile_Map_.GetSpecificTile({ x_1 , y_2 - TILE_SIZE/2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 , y_2 - TILE_SIZE/2 }));
                if(Tile_Map_.GetSpecificTile({ x_2 , y_2 - TILE_SIZE/2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_2 , y_2 - TILE_SIZE/2 }));
            }
        }
        else
        {
            if (object->GetComponentByTemplate<RigidBody>()->GetViewingDirection().y > 0)
            {
                if (Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_1 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_1 }));
                if (Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_2 }));
                if (Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_0 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_0 }));
                if (Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE/2, y_1 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE/2, y_1 }));
                if (Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE/2, y_2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE/2, y_2 }));
                if (Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE/2, y_0 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE/2, y_0 }));
                if (Tile_Map_.GetSpecificTile({ x_0 , y_1 + TILE_SIZE/2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_0 , y_1 + TILE_SIZE/2 }));
                if (Tile_Map_.GetSpecificTile({ x_1 , y_1 + TILE_SIZE/2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 , y_1 + TILE_SIZE/2 }));
                if (Tile_Map_.GetSpecificTile({ x_2 , y_1 + TILE_SIZE/2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_2 , y_1 +TILE_SIZE/2 }));
            }
            else
            {
                if (Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_1 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_1 }));
                if (Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_2 }));
                if (Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_0 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_1 + TILE_SIZE / 2, y_0 }));
                if (Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE/2, y_1 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE/2, y_1 }));
                if (Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE/2, y_0 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE/2, y_0 }));
                if (Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE/2, y_2 }) != nullptr)
                    tile_list.push_back(Tile_Map_.GetSpecificTile({ x_2 - TILE_SIZE/2, y_2 }));
            }
        }
    }
    void GroundCheck(Object* object)
    {
        float x_0 = object->GetTransform().GetTranslation().x;
        float x_1 = object->GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[1].x;
        float x_2 = object->GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[0].x;
        float y_2 = object->GetComponentByTemplate<Collision>()->GetCollisionCalculateTRS()[1].y;
        if (Tile_Map_.GetSpecificTile({ x_1 , y_2 - TILE_SIZE/2 }) != nullptr)
            ground_list.push_back(Tile_Map_.GetSpecificTile({ x_1 , y_2 - TILE_SIZE/2 }));
        if (Tile_Map_.GetSpecificTile({ x_2 , y_2 - TILE_SIZE/2 }) != nullptr)
            ground_list.push_back(Tile_Map_.GetSpecificTile({ x_2 , y_2 - TILE_SIZE/2 }));
        if (Tile_Map_.GetSpecificTile({ x_0 , y_2 - TILE_SIZE/2 }) != nullptr)
            ground_list.push_back(Tile_Map_.GetSpecificTile({ x_0 , y_2 - TILE_SIZE/2 }));
    }



private:
	//Objectmanager* temp_obj = nullptr;
	std::vector<Object*> collision_list;
    std::vector<Object*> tile_list;
    std::vector<Object*> ground_list;
    std::vector<Object*> static_list;
    std::vector<Object*> projectile_list;
    std::vector<Object*> capture_list;
    std::vector<Object*> dynamic_list;
	std::vector<Object*> checkpoint_list;
	std::vector<Object*> trigger_list;
    Object* door = nullptr;
        int previous_size = 0;
    //vector2 windowsize = vector2{ 1280, 960 };
};

extern Physics Physics_;