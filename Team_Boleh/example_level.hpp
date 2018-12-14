#pragma once
#include "Object.hpp"
#include "Objectmanager.hpp"
#include "State.hpp"
#include <cmath>
#include "Sound.hpp"

class example : public State
{
public:
	example()
	{
		information_ = State_Information::Game;
	}

	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;
	// You need add sprite or animation.
	Object* BuildAndRegisterDynamicObject(std::string object_name, vector2 position, vector2 scale);
	Object* BuildAndRegisterStaticObject(std::string object_name, vector2 position, vector2 scale);
	void SwordPosition(std::string player_str, std::string sword_str);
	void ForProtoType(Object* object, Object* opponent, float vel_come);
	void snailoption( Object* effect,Object* knife, float angle, float& angle_);
	void Enchanted(Object* sword, Object* effect, Object* card1, Object* card2, float dt);
	void thrust(Object* sword,Object* player, float force);
	void FollowMe(vector2 mouse, Object* flower);
	void Flow_leaf(std::vector<Object*> flower);
	void Stretch(Object* sword, float bigger);
	void Power_shot();
	void find(std::string card_);
	Object* AwesomeEfftect(std::string stuff, vector2 position);
	void ComePlayer(Object* object, Object* opponent, float vel_come);
	void MakeManyEffect(std::string card);
	void Shot(std::string name);

private:
	float gravity_up = 1;
	bool check = false;
	float pm = 1;
	bool change_sword = false;
	float rota_angle = 0.f, rota_angle1 = 0.f;
	float dt_sum = 0;
	float dt_power_shot = 0;
	float card_velo = 20;
	float rotation_ = 10;
	bool isshot = false;
	float far = 1;
	char shot_char = 0;
	vector2 direction = 0;

	Object* player;
	std::string a_stuff;
	std::string shot_string = "shot_";
    Object *sword, *sonic, *background, *spark, *dia, 
	*heart, *scol, *slime, *dia1, *heart1, *door, *attack, *spade, *clover;
    std::vector<std::string> shot_vector;
    std::vector<Object*> card_list;
    std::vector<Object*> dump;
    Object* opponent1, *opponent2, *opponent3,* opponent4 ;

};

