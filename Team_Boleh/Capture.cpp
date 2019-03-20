#include "Capture.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include <iostream>

bool Capture::Initialize(Object* Ob)
{
	if(object == nullptr)
		object = Ob;
	return true;
}

void Capture::Update(float dt)
{
	vector2 mouse_pos = Input::GetMousePos();


	//std::cout << Graphics_.camera_zoom << std::endl;
	//std::cout << mouse_pos.x << ", " << mouse_pos.y << std::endl;

	object->SetTranslation(mouse_pos);

	if(Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		cheese = true;
		object->GetComponentByTemplate<Animation>()->ChangeAnimation("cheese");
		Capturing();
		CreateCaptureObject();
	}

	if(cheese)
	{
		object->GetMesh().Decrease_Alpha(5);
		if (object->GetMesh().GetColor(0).Alpha <= 15)
		{
			object->GetComponentByTemplate<Animation>()->ChangeAnimation("basic_camera");
			object->GetMesh().ChangeColor({ 255,255,255,255 });
			cheese = false;
		}
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
		if (obj->GetObjectType() == ObjectType::None && obj.get() != object)
		{
			vector2 save_obj_pos = obj->GetTransform().GetTranslation();
			vector2 scale = obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale()/2;

			vector2 min_obj = { save_obj_pos.x - scale.x, save_obj_pos.y - scale.y };
			vector2 max_obj = { save_obj_pos.x + scale.x, save_obj_pos.y + scale.y };
			

			if ((min_obj.x >= min_pos.x)&& (max_obj.x <= max_pos.x) && 
				(min_obj.y >= min_pos.y) && (max_obj.y <= max_pos.y))
			{
				Object* temp = new Object(*obj.get());
				temp->SetObjectType(ObjectType::Capture_Obj);

				if(auto temp_animation = temp->GetComponentByTemplate<Animation>();
					temp_animation != nullptr)
				{
					temp_animation->SetIsActive(false);
				}

				capture_object.push_back(temp);

				auto player_ = Objectmanager_.GetPlayer();
				player_->SetTranslation(reset_pos);

				std::cout << capture_object.size() << std::endl;
			}
		}
	}
}

void Capture::CreateCaptureObject()
{
	for(auto c_obj : capture_object)
	{
		Objectmanager_.AddObject(c_obj);
	}
	capture_object.clear();
}
