#include "Sword.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include "status.hpp"
#include "Character.hpp"
#include <iostream>

Sword::Sword(Object * player)
{
	owner = player;
}

bool Sword::Initialize(Object * Ob)
{
	if (object == nullptr)
	{
		object = Ob;
		auto temp_translation = owner->GetTransform().GetTranslation();
		object->SetScale({ 75.0f, 75.0f });
		object->SetTranslation(temp_translation);
		object->SetMesh(mesh::CreateBox());
		object->AddComponent(new Sprite());
		object->GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/trash.png");
		object->AddComponent(new Collision(box_, {}, { 40.0f, 40.0f }));
		object->AddComponent(new RigidBody());
		object->GetComponentByTemplate<Collision>()->SetRestitutionType(RestitutionType::none);
		object->AddComponent(new Character(ObjectType::sword));
		object->AddComponent(new Status(5, 1, 1.f));
		object->SetDepth(0.978f);
	}
	return true;
}

void Sword::Update(float dt)
{
	/*std::cout << owner->GetTransform().GetTranslation().x << ", " <<
		owner->GetTransform().GetTranslation().y << std::endl;
		*/

	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		object->GetComponentByTemplate<Collision>()->ToggleIsDamaged();
	}

	SwordMove(Input::GetMousePos(Graphics::checking_zoom));
}

void Sword::SetOwner(Object* player)
{
	owner = player;
}

void Sword::Delete()
{
}

void Sword::SwordMove(vector2 mouse_position)
{
	vector2 swing_direction = normalize(vector2(mouse_position.x - owner->GetTransform().GetTranslation().x,
		mouse_position.y - owner->GetTransform().GetTranslation().y));
	object->SetTranslation(vector2(
		owner->GetTransform().GetTranslation().x + swing_direction.x *owner->GetTransform().GetScale().x / 1.5f,
		owner->GetTransform().GetTranslation().y + swing_direction.y *owner->GetTransform().GetScale().y / 1.5f));
	float anglerad = atan2(mouse_position.y - owner->GetTransform().GetTranslation().y, mouse_position.x - owner->GetTransform().GetTranslation().x);
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
