#pragma once
#include "System.hpp"
#include "Objectmanager.hpp"
#include "Collision.hpp"
#include "Reaction.hpp"

class Physics : public System
{
public:
	bool Initialize() override;
	void Update(float dt) override;
	void PhysicsObjectUpdate(Objectmanager* objectmanager);
	void Quit() override;

	void ChangeRestitutionOfOjbect(Object object1, Object object2);

	// This function is used by intersection check. You do not use it for collision check.
	bool CollisionOnAxis(vector2 Axis, std::vector<vector2> owner, std::vector<vector2> object);
	// This function is used by upper function (CollisionOnAxis). It take interval between vertices. 
	void Interval(std::vector<vector2>vertices, vector2 Axis, float& min, float& max);
	// This function convert vector to line.
	std::vector<vector2> VectorToLine(Object object);
	// This is real intersection check which you use.
	bool IntersectionCheck(Object object1, Object object2);
        
        // This function return true if object is out of window area. 
        bool OutOfCheckBoundary(Object* object);

private:
	Objectmanager* temp_obj = nullptr;
	std::vector<Object*> collision_list;
        vector2 windowsize = vector2{ 1280, 960 };
};
