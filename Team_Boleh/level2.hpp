#pragma once
#include "State.hpp"

class level2 : public State
{
public:
	level2()
	{
		information_ = State_Information::Game;
	}

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
	void BossMovement(Object* boss_monster, Object* player, float dt);
	void Shot(std::string name);

private:
	float dt_sum =0, dt_boss = 0;
	float rota_angle = 0, rota_angle1 =0;
	float rotate = 0;
	float card_velo = 20;
	float far = 1;
	bool change_sword = false;
	int shot_char = 0;
	Object* player, *background,*sword, *spade, *clover, *spade1, *door, *clover1, *spark, *boss, *dia, *heart;
	std::vector<Object*> card_list;
	std::string shot_string;
	bool check1 = true;
	bool check2 = true;
};