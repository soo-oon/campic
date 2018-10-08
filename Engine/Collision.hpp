#pragma once
#include "Objectmanager.hpp"

class Collision : public Component
{
public:
	bool collision_(vector2 Axis, std::vector<vector2> owner, std::vector<vector2> object);
        void Interval(std::vector<vector2>vertices, vector2 Axis, float& min, float& max);
        std::vector<vector2> line(std::vector<vector2> axis);
        bool intersection_check(std::vector<vector2> owner, std::vector<vector2> object);

        bool Initialize(Object* Ob) override;
        void Update(float dt) override;
        void Delete() override;

private:

        std::vector<vector2> mesh_owner;
	Objectmanager object_manager;
};
