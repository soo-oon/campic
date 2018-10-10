#pragma once
#include "Component.hpp"
#include "Transform.hpp"
#include "WorldPhysics.h"
#include "Object.hpp"
#include "StateManager.hpp"

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
    vector2 GetPosition();
    void AddForce(vector2 force);
    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;
private:
	
    vector2 force_accumlator; // mess 
    vector2 velocity;
    vector2 position;
    float friction = 0.995f;
    float gravity;
    float inverse_mass = 1;
    float rotation;
    float torque;
    float angler_velosity;
    float inverse_inertia;

    bool collision_switch = false;

    Transform transform;
};
