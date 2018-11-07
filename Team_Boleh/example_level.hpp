#pragma once
#include "Object.hpp"
#include "Objectmanager.hpp"
#include "State.hpp"
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
    void SwordPosition(std::string player_str, std::string sword_str);

private:
    float gravity_up = 1;
	bool check = false;
	float pm = 1;
	float limit_time = 0;
	float rotation_value = 10;
	vector2 direction = 0;
    std::vector<vector2> opponent;
    std::vector<vector2> mesh_p;
    std::vector<vector2> static_opponent;

    Object* player, *sword, *sonic, *dr_s, *background;

};

