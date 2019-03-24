#include "Capture.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include <iostream>
#include "State.hpp"

bool Capture::Initialize(Object* Ob)
{
	if(object == nullptr)
		object = Ob;
	return true;
}

void Capture::Update(float dt)
{
	vector2 mouse_pos = Input::GetMousePos();

	object->SetTranslation(mouse_pos);

	if(Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		cheese = true;
		Capturing();
	}

}

void Capture::Delete()
{
}

void Capture::Capturing()
{
	vector2 object_pos = object->GetTransform().GetTranslation();
	vector2 object_size = object->GetTransform().GetScale()/2;
	vector2 min_pos = { object_pos.x - object_size.x, object_pos.y - object_size.y};
	vector2 max_pos = { object_pos.x + object_size.x, object_pos.y + object_size.y };
        

	for(auto& obj : Objectmanager_.GetObjectMap())
	{
		if ((obj->GetObjectType() == ObjectType::None || obj->GetObjectType() == ObjectType::Player)
			&& obj.get() != object)
		{
			vector2 save_obj_pos = obj->GetTransform().GetTranslation();
			
			vector2 scale = obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale()/2;
			auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();

			vector2 min_obj = { save_obj_pos.x - scale.x, save_obj_pos.y - scale.y };
			vector2 max_obj = { save_obj_pos.x + scale.x, save_obj_pos.y + scale.y };


			vector2 reset_min = { reset_pos.x - player_->GetTransform().GetScale().x / 2, reset_pos.y - player_->GetTransform().GetScale().x / 2 };
			vector2 reset_max = { reset_pos.x + player_->GetTransform().GetScale().x / 2, reset_pos.y + player_->GetTransform().GetScale().x / 2 };

			if ((min_obj.x >= reset_max.x) || (max_obj.x <= reset_min.x) ||
				(min_obj.y >= reset_max.y) || (max_obj.y <= reset_min.y))
			{
				if ((min_obj.x >= min_pos.x) && (max_obj.x <= max_pos.x) &&
					(min_obj.y >= min_pos.y) && (max_obj.y <= max_pos.y))
				{
					Object* temp = new Object(*obj.get());
					temp->GetComponentByTemplate<RigidBody>()->SetGravity(0);
					temp->GetComponentByTemplate<RigidBody>()->SetVelocity(0);
					temp->GetComponentByTemplate<Collision>()->ChangeCollisionBoxTranslation(temp->GetTransform().GetTranslation());
					temp->SetObjectType(ObjectType::Capture_Obj);

					if (auto temp_animation = temp->GetComponentByTemplate<Animation>();
						temp_animation != nullptr)
					{
						temp_animation->SetIsActive(false);
					}

					player_->SetTranslation(reset_pos);
                    player_->GetComponentByTemplate<Collision>()->ChangeCollisionBoxTranslation(reset_pos);
                    player_->GetComponentByTemplate<Collision>()->SetIsGround(false);
					Objectmanager_.AddObject(temp);
					break;
				}
			}
		}
	}
}
