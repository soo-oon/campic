#pragma once
#include "Component.hpp"
#include <vector>

struct vector2;

class Player : public Component
{
public:
	bool Initialize(Object* Ob);
	void Update(float dt);
	void Delete();
	void MovePlayer();
	void SetCardList(std::string card);
	void ClearCardList();
	std::vector<std::string> GetCardList();
	void PlayerMove(vector2 mouse_position);

private: 
	std::vector<std::string> card_list = {};
};
