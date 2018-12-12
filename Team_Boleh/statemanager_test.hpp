#pragma once
#include "State.hpp"

class test_statemanager : public State
{
public:
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;
	Object* BuildAndRegisterDynamicObject(std::string object_name, vector2 position, vector2 scale);
	Object* BuildAndRegisterStaticObject(std::string object_name, vector2 position, vector2 scale);
	void SwordSwing(vector2 mouse_position, Object* player, Object* sword);
	void Attact(Object* object);
	void snailoption(Object* effect, Object* knife, float angle, float& angle_);
	void Enchanted(Object* sword, Object* effect, Object* card1, Object* card2, float dt);
	void PlayerSwing(vector2 mouse_position, Object* player);
	void find(std::string card_);

private:
	float dt_sum =0;
	float rota_angle = 0, rota_angle1 =0;
	float card_velo = 20;
	float far = 1;
	bool change_sword = false;
	Object* player, *background,*sword, *spade, *clover, *spade1, *door, *clover1, *spark;
	std::vector<Object*> card_list;
	bool check1 = true;
	bool check2 = true;
};