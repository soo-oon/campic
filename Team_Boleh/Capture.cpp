#include "Capture.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include <iostream>
#include "State.hpp"
#include "Projectile.hpp"

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

	for(int i =0; i<static_cast<int>(polaroid_object.size()); ++i)
	{
		polaroid_object[i]->Update();

		/*if(polaroid_object[i]->IsDead())
		{
			polaroid_object.erase(polaroid_object.begin() + i);
		}*/
	}

	if(Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		cheese = true;
		Capturing();
		CreatePolaroidObject();
		CreateCaptureObject();
	}
        if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_MIDDLE))
        {
            SlowMode(0.5);
        }
        if (Input::IsMouseReleased(GLFW_MOUSE_BUTTON_MIDDLE))
        {
            SlowMode(1);
        }
    if (Input::IsKeyTriggered(GLFW_KEY_6))
        {
            m_c_filter = Filter::Jump;
            object->GetMesh().ChangeColor({ 0,0,255,255 });
        }
        if (Input::IsKeyTriggered(GLFW_KEY_7))
        {
            m_c_filter = Filter::None;
            object->GetMesh().ChangeColor({ 255,255,255,255 });
        }
        if (Input::IsKeyTriggered(GLFW_KEY_8))
        {
            m_c_filter = Filter::Speed;
            object->GetMesh().ChangeColor({ 0,255,0,255 });
        }

}

void Capture::Delete()
{
}

void Capture::Polaroid::Update()
{
	/*obj->GetMesh().Decrease_Alpha(5);

	if (obj->GetMesh().GetColor(0).Alpha <= 5)
	{
		obj->GetMesh().SetAlphaZero();
		obj->SetObjectDead();
		isdead = true;
	}*/
}

void Capture::SlowMode(float fric)
{
    vector2 object_pos = object->GetTransform().GetTranslation();
    vector2 object_size = object->GetTransform().GetScale() / 2;
    vector2 min_pos = { object_pos.x - object_size.x, object_pos.y - object_size.y };
    vector2 max_pos = { object_pos.x + object_size.x, object_pos.y + object_size.y };

    for (auto& obj : Objectmanager_.GetObjectMap())
    {
        if ((obj->GetObjectType() == ObjectType::None || obj->GetObjectType() == ObjectType::Player
            || obj->GetObjectType() == ObjectType::Projectile)
            && obj.get() != object)
        {
            vector2 save_obj_pos = obj->GetTransform().GetTranslation();

            vector2 scale = obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale() / 2;
            auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();

            vector2 min_obj = { save_obj_pos.x - scale.x, save_obj_pos.y - scale.y };
            vector2 max_obj = { save_obj_pos.x + scale.x, save_obj_pos.y + scale.y };

            if (auto physics = obj.get()->GetComponentByTemplate<RigidBody>(); physics != nullptr)
            {
                if ((min_obj.x >= min_pos.x) && (max_obj.x <= max_pos.x) &&
                    (min_obj.y >= min_pos.y) && (max_obj.y <= max_pos.y))
                {
                    physics->SetSlowMode(fric);
                }
                else
                    physics->SetSlowMode(1);
            }
            
        }
    }
}

void Capture::Capturing()
{
	vector2 object_pos = object->GetTransform().GetTranslation();
	vector2 object_size = object->GetTransform().GetScale()/2;
	vector2 min_pos = { object_pos.x - object_size.x, object_pos.y - object_size.y};
	vector2 max_pos = { object_pos.x + object_size.x, object_pos.y + object_size.y };
        
	for(auto& obj : Objectmanager_.GetObjectMap())
	{
		if ((obj->GetObjectType() == ObjectType::None || obj->GetObjectType() == ObjectType::Player
			 || obj->GetObjectType() == ObjectType::Projectile)
			&& obj.get() != object)
		{
			vector2 save_obj_pos = obj->GetTransform().GetTranslation();
			
			vector2 scale = obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale()/2;
			auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();

			if (player_ != nullptr)
			{
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
                                                if (m_c_filter == Filter::Jump)
                                                {
                                                    temp->GetComponentByTemplate<Collision>()->SetFilter(Filter::Jump);
                                                    temp->GetMesh().ChangeColor({ 0,0,255,255 });
                                                }
                                                if (m_c_filter == Filter::Speed)
                                                {
                                                    temp->GetComponentByTemplate<Collision>()->SetFilter(Filter::Speed);
                                                    temp->GetMesh().ChangeColor({ 0,255,0,255 });
                                                }
					    temp->SetObjectType(ObjectType::Capture_Obj);

						if (obj->GetObjectType() == ObjectType::Projectile)
						{
							obj->SetIsDead(true);
						}

						if (auto temp_animation = temp->GetComponentByTemplate<Animation>();
							temp_animation != nullptr)
						{
							temp_animation->SetIsActive(false);
						}

						if (obj->GetObjectType() == ObjectType::Player)
						{
							player_->SetTranslation(reset_pos);
							player_->GetComponentByTemplate<Collision>()->ChangeCollisionBoxTranslation(reset_pos);
							player_->GetComponentByTemplate<Collision>()->SetIsGround(false);
						}
						
						capture_object.push_back(temp);
						iscreate = true;
					}
				}
			}
		}
	}
}

void Capture::CreateCaptureObject()
{
	if (!capture_object.empty())
	{
		for (auto obj : capture_object)
		{
			Objectmanager_.AddObject(obj);
		}
	}

	if(!polaroid_object.empty())
	{
		for(auto obj : polaroid_object)
		{
			Objectmanager_.AddObject(obj->GetObject());
		}
	}

	capture_object.clear();
	polaroid_object.clear();
}

void Capture::CreatePolaroidObject()
{
	if (iscreate)
	{
		for(auto obj : capture_object)
		{
			Polaroid* temp = new Polaroid(obj);
			polaroid_object.push_back(temp);
		}
		iscreate = false;
	}
}
