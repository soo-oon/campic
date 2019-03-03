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

class Physics
{
public:
	bool Initialize();
	void Update(float dt);

	//void PhysicsObjectUpdate(Objectmanager* objectmanager);

	void Quit();

	void ChangeRestitutionOfOjbect(Object object1, Object object2);

	// This function is used by intersection check. You do not use it for collision check.
	bool CollisionOnAxis(vector2 Axis, std::vector<vector2> owner, std::vector<vector2> object);
	// This function is used by upper function (CollisionOnAxis). It take interval between vertices. 
	void Interval(std::vector<vector2>vertices, vector2 Axis, float& min, float& max);
	// This function convert vector to line.
	std::vector<vector2> VectorToLine(Object object);
	// This is real intersection check which you use.
	bool IntersectionCheck(Object object1, Object object2);
        // This is intersection check which is AABB version for thin 
        bool IntersectionCheck_AABB(Object object1, Object object2);
        
		void ResetPreviousSize() { previous_size = 0; }

        // This function return true if object is out of window area. 
        bool OutOfCheckBoundary(Object* object);



private:
	//Objectmanager* temp_obj = nullptr;
	std::vector<Object*> collision_list;
        int previous_size = 0;
    //vector2 windowsize = vector2{ 1280, 960 };
};

extern Physics Physics_;