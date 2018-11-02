#pragma once
#include "System.hpp"
#include "Objectmanager.hpp"
#include <list>

class Physics : public System
{
public:
	bool Initialize() override;
	void Update(float dt) override;
	void PhysicsObjectUpdate(Objectmanager* objectmanager);
	void Quit() override;

	// This function is used by intersection check. You do not use it for collision check.
	bool Collision_on_axis(vector2 Axis, std::vector<vector2> owner, std::vector<vector2> object);
	// This function is used by upper function (Collision_on_axis). It take interval between vertices. 
	void Interval(std::vector<vector2>vertices, vector2 Axis, float& min, float& max);
	// This function convert vector to line.
	std::vector<vector2> Vector_to_line(Object object);
	// This is real intersection check which you use.
	bool Intersection_check(Object object1, Object object2);

private:
	Objectmanager* temp_obj = nullptr;
	std::vector<Object> collision_list;
};
