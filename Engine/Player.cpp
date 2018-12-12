#include "Player.hpp"
#include "Input.hpp"
#include "RigidBody.hpp"
#include "Character.hpp"
#include "status.hpp"
#include <iostream>

bool Player::Initialize(Object * Ob)
{
	if (object == nullptr)
	{
		object = Ob;
		object->SetTranslation({ 0,0 });
		object->SetScale({ 100.0f, 100.0f });
		object->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
		object->AddComponent(new RigidBody());
		object->AddComponent(new Animation("asset/images/action.png", "zelda_down", 10, 0.1f));
		object->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/attack.png", "attack", 3, 0.25f, false);
		object->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/action_c.png", "zelda_up", 10, 0.1f);
		object->AddComponent(new Collision(box_, {}, { 100.0f, 100.0f }));
		object->AddComponent(new Character(ObjectType::player));
		object->AddComponent(new Status(5, 1, 1.f));
	}
	return true;
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
	std::cout << object->GetTransform().GetTranslation().x << ", " <<
		object->GetTransform().GetTranslation().y << std::endl;

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
