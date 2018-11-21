#pragma once
#include "Object.hpp"
#include "Objectmanager.hpp"
#include "State.hpp"
#include <cmath>
#include "Sound.hpp"

class example : public State
{
public:
	void blackhole(Object* Ob, Object* Ob1);
    void move_convex_object(float dt, Object* Ob);
	void Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;
    // You need add sprite or animation.
    Object* BuildAndRegisterDynamicObject(std::string object_name, vector2 position, vector2 scale);
    Object* BuildAndRegisterStaticObject(std::string object_name, vector2 position, vector2 scale);
    void SwordSwing(vector2 mouse_position, Object* player, Object* sword);
    void Attact(Object* object);
    void SwordPosition(std::string player_str, std::string sword_str);
    void ForProtoType(Object* object, Object* opponent, float vel_come);
    void snailoption( Object* effect,Object* knife, float angle, float& angle_);
    void Enchanted(Object* sword, Object* effect, Object* card1, Object* card2, float dt);
    void thrust(Object* sword,Object* player, float force);

private:
	float gravity_up = 1;
	bool check = false;
	float pm = 1;
	float limit_time = 0;
	bool change_sword = false;
	float rota_angle = 0.f, rota_angle1 = 0.f;
	float dt_sum = 0;
	float card_velo = 20;
	float rotation_ = 10;
	bool isshot = false;
	vector2 direction = 0;

    Object* player, *sword, *sonic, *background, *spark, *dia, *heart, *scol, *slime, *dia1, *heart1, *door, *shot;

};

