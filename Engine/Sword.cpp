#include "Sword.hpp"

Sword::Sword(Object * player)
{
	owner = player;
}

bool Sword::Initialize(Object * Ob)
{
	object = Ob;
	return true;
}

void Sword::Update(float dt)
{
}
void Sword::MoveWithPlayer(vector2 mouse_position, Object* player)
{
	vector2 swing_direction = normalize(vector2(mouse_position.x - player->GetTransform().GetTranslation().x,
		mouse_position.y - player->GetTransform().GetTranslation().y));
	object->SetTranslation(vector2(
		player->GetTransform().GetTranslation().x + swing_direction.x *player->GetTransform().GetScale().x / 1.5f,
		player->GetTransform().GetTranslation().y + swing_direction.y *player->GetTransform().GetScale().y / 1.5f));
	float anglerad = atan2(mouse_position.y - player->GetTransform().GetTranslation().y, mouse_position.x - player->GetTransform().GetTranslation().x);
	float angledeg = (180 / 3.14f)* anglerad;
	object->SetRotation(angledeg - 90);
	//sword->GetComponentByTemplate<Collision>()->GetCollisionTransform().SetRotation(angledeg - 90);
//float a = dot(sword->GetTransform().GetTranslation(), vector2(0, 1))/ magnitude(sword->GetTransform().GetTranslation());
//if(mouse_position.x > player->GetTransform().GetTranslation().x)
//{
//    std::cout <<"mouse : "<< mouse_position.x <<"player : " << player->GetTransform().GetTranslation().x << std::endl;
//    a = 360 - acos(a)*(180 / 3.14);
//}
//else
//a = acos(a)*(180/3.14);
//std::cout << a << std::endl;
//sword->SetRotation(a);
}