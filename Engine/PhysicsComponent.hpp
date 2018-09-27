#pragma once
#include "Component.hpp"
#include <glm/vec2.hpp>
#include "Transform.hpp"

class Physics : public Component
{
	//void collision();
	//void movement();
	//void gravity();
public:
	void CollisionOn();
	void SetMass(float mass);
	void SetVelocity(glm::vec2 velocity);
	void AddForce(glm::vec2 force);
	bool Initialize();
	void Update(float dt);
	void ShutDown();
private:
	glm::vec2 force_accumlator; // mess 
	glm::vec2 velocity;
	glm::vec2 position;
	float inverse_mass;
	float rotation;
	float torque;
	float angler_velosity;
	float inverse_inertia;

	bool collision_switch = false;

	Transform transform;
};
