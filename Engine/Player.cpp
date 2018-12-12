#include "Player.hpp"
#include "Input.hpp"
#include "RigidBody.hpp"

bool Player::Initialize(Object * Ob)
{
	object = Ob;
	return false;
}

void Player::Update(float dt)
{
	MovePlayer();
}

void Player::Delete()
{
}

void Player::MovePlayer()
{
	if (Input::IsKeyPressed(GLFW_KEY_W))
	{
		object->GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(0, 5));
	}
	if (Input::IsKeyPressed(GLFW_KEY_A))
	{
		object->GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(-5, 0));
	}
	if (Input::IsKeyPressed(GLFW_KEY_S))
	{
		object->GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(0, -5));
	}
	if (Input::IsKeyPressed(GLFW_KEY_D))
	{
		object->GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(5, 0));
	}

}

void Player::SetCardList(std::string card)
{
	card_list.push_back(card);
}

void Player::ClearCardList()
{
	card_list.clear();
}

std::vector<std::string> Player::GetCardList()
{
	return card_list;
}
