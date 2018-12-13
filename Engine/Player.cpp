#include "Player.hpp"
#include "Input.hpp"
#include "RigidBody.hpp"
#include "Character.hpp"
#include "status.hpp"
#include <iostream>
#include "Graphics.hpp"

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
	PlayerMove(Input::GetMousePos(Graphics::checking_zoom));
}

void Player::Delete()
{
}

void Player::MovePlayer()
{
	if (Input::IsKeyPressed(GLFW_KEY_W))
	{
		object->GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(0, 2));
	}
	if (Input::IsKeyPressed(GLFW_KEY_A))
	{
		object->GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(-2, 0));
	}
	if (Input::IsKeyPressed(GLFW_KEY_S))
	{
		object->GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(0, -2));
	}
	if (Input::IsKeyPressed(GLFW_KEY_D))
	{
		object->GetComponentByTemplate<RigidBody>()->AddVelocity(vector2(2, 0));
	}

	if (dot(object->GetComponentByTemplate<RigidBody>()->GetVelocity(), vector2(0, 1)) > 0)
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("zelda_up");
	else
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("zelda_down");

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

void Player::PlayerMove(vector2 mouse_position)
{
	vector2 swing_direction = normalize(vector2(mouse_position.x - object->GetTransform().GetTranslation().x,
		mouse_position.y - object->GetTransform().GetTranslation().y));
	float anglerad = atan2(mouse_position.y - object->GetTransform().GetTranslation().y, mouse_position.x - object->GetTransform().GetTranslation().x);
	float angledeg = (180 / 3.14f)* anglerad;
	object->SetRotation(angledeg - 270);

	//std::cout << angledeg - 270 << std::endl;
}
