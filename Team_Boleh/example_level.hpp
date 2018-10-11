#pragma once
#include "Stage.hpp"
#include "Object.hpp"
#include "Objectmanager.hpp"
#include "WorldPhysics.h"

class example : public State
{
public:
	void blackhole(Object* Ob);
    void move_enemy(float dt, Object* Ob);
    bool Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;

private:
	float pm = 1;
	float limit_time = 0;
	float rotation_value = 10;
	vector2 direction = 0;
    std::vector<vector2> opponent;
    std::vector<vector2> mesh_p;
    std::vector<vector2> static_opponent;
};

vector2 multi_plus(Object *ob, size_t i);
