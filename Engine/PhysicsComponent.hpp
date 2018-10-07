#pragma once
#include "Component.hpp"
#include "Transform.hpp"
#include "WorldPhysics.h"

class Physics : public Component
{
	//void collision();
	//void movement();
	//void gravity();
public:
	void CollisionOn();
	void SetMass(float mass);
	void SetVelocity(vector2 velocity);
	vector2 GetVelocity();
	void AddForce(vector2 force);
	bool Initialize();
	void Update(float dt);
	void Delete();
private:
	vector2 force_accumlator; // mess 
	vector2 velocity;
	vector2 position;
	float inverse_mass;
	float rotation;
	float torque;
	float angler_velosity;
	float inverse_inertia;

	bool collision_switch = false;

	Transform transform;
};
