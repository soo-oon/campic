#pragma once
#include "Stage.hpp"
#include "Object.hpp"
#include "Objectmanager.hpp"
#include "WorldPhysics.h"

class example : public State
{
public:
    example()
    {
        objectmanager = new Objectmanager();
    }

    void move_enemy(float dt, Object* Ob);

    bool Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;
private:
	float pm = 1;
	float limit_time = 0;
	float rotation_value = 10;
    std::vector<vector2> opponent;
    std::vector<vector2> mesh_p; 
};

vector2 multi_plus(Object *ob, size_t i);
