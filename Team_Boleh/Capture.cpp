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
	vector2 mouse_pos = Input::GetMousePos(Graphics_.camera_zoom);
	object->SetTranslation(mouse_pos);

	//std::cout << capture_object.size() << std::endl;

	if(Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
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
		if (obj->GetObjectType() == ObjectType::None && obj.get() != object)
		{
			vector2 save_obj_pos = obj->GetTransform().GetTranslation();
			if (save_obj_pos.x >= min_pos.x && save_obj_pos.x <= max_pos.x &&
				save_obj_pos.y >= min_pos.y && save_obj_pos.y <= max_pos.y)
			{
				capture_object.push_back(obj.get());
				capture_object[capture_object.size() - 1]->GetComponentByTemplate<Animation>()->SetIsActive(false);
			}
		}
	}
}
