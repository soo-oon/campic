#include "Capture.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include <iostream>
#include "State.hpp"
#include "Projectile.hpp"
#include "Player.hpp"

bool Capture::Initialize(Object* Ob)
{
    if (object == nullptr)
    {
        object = Ob;

        vector2 size = object->GetTransform().GetScale();
        zoomobject = new Object();
        zoomobject->SetMesh(mesh::CreateBox());
        zoomobject->SetTranslation({ object->GetTransform().GetTranslation().x + size.x/1.8f, object->GetTransform().GetTranslation().y});
        zoomobject->SetDepth(object->GetTransform().GetDepth()+0.1f);
        zoomobject->SetScale({ 30, size.y });
        zoomobject->SetObjectType(ObjectType::Capture_Camera);
        zoomobject->AddComponent(new Sprite("asset/images/zoom.png"));

        zoombutton = new Object();
        zoombutton->SetMesh(mesh::CreateBox());
        zoombutton->SetDepth(object->GetTransform().GetDepth());
        zoombutton->SetScale({ 30, 30 });
        zoombutton->SetObjectType(ObjectType::Capture_Camera);
        zoombutton->AddComponent(new Sprite("asset/images/zoom_button.png"));

        zoomobject->SetParent(&object->GetTransform());
        Objectmanager_.AddObject(zoomobject);
        Objectmanager_.AddObject(zoombutton);
    }

    zoom_min_value = 1.0f;
    zoom_max_value = 2.5f;

    return true;
}

void Capture::Update(float dt)
{
    CameraZoom();
    ZoomObjectUpdate(dt);

    if (player == nullptr)
    {
        player = StateManager_.GetCurrentState()->GetPlayerObjectPointer();
    }

    if (Input::IsKeyTriggered(GLFW_KEY_KP_3))
        isCollisionSizeBig = true;
    if (Input::IsKeyTriggered(GLFW_KEY_KP_6))
        isCollisionSizeBig = false;

	//Capture_Camera_Move();

    /*for(int i =0; i<static_cast<int>(polaroid_object.size()); ++i)
    {
            polaroid_object[i]->Update();

            if(polaroid_object[i]->IsDead())
            {
                    polaroid_object.erase(polaroid_object.begin() + i);
            }
    }*/

    if (IsCaptureArea())
    {
		if (StateManager_.GetCurrentState()->GetCaptureLimit() > 0)
		{
			if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
			{
				--StateManager_.GetCurrentState()->GetCaptureLimit();
				cheese = true;
				Capturing();
				CreatePolaroidObject();
				CreateCaptureObject();
			}
		}
    }
	CameraZoomInOut();
	SetOrigianlSize();
	SlowMode();

    if (Input::IsKeyTriggered(GLFW_KEY_6))
    {
        m_c_filter = Filter::Jump;
        object->GetMesh().ChangeColor({0, 0, 255, 255});
    }
    if (Input::IsKeyTriggered(GLFW_KEY_7))
    {
        m_c_filter = Filter::None;
        object->GetMesh().ChangeColor({255, 255, 255, 255});
    }
    if (Input::IsKeyTriggered(GLFW_KEY_8))
    {
        m_c_filter = Filter::Speed;
        object->GetMesh().ChangeColor({0, 255, 0, 255});
    }
}

void Capture::Delete()
{
}

void Capture::Capture_Camera_Move()
{
	vector2 current_mouse_pos = Input::GetMousePos();

	if(prev_mouse_pos != current_mouse_pos)
	{
		object->SetTranslation(current_mouse_pos);
		prev_mouse_pos = current_mouse_pos;
	}
	else
	{
		if(auto player_ = StateManager_.GetCurrentState()->GetPlayerObjectPointer();
			player_ != nullptr)
		{
		}
	}

}

void Capture::SetZoomMinMax(float max, float min)
{
    zoom_max_value = max;
    zoom_min_value = min;
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

bool Capture::IsCaptureArea()
{
    bool result = false;
    capture_area_contian_object.clear();
    not_area_contian_object.clear();

    vector2 object_pos = object->GetTransform().GetTranslation();
    vector2 object_size = object->GetTransform().GetScale() / 2;
    vector2 min_pos = {object_pos.x - object_size.x, object_pos.y - object_size.y};
    vector2 max_pos = {object_pos.x + object_size.x, object_pos.y + object_size.y};

    for (auto& obj : Objectmanager_.GetObjectMap())
    {
        if ((obj->GetObjectType() == ObjectType::None || obj->GetObjectType() == ObjectType::Player ||
            obj->GetObjectType() == ObjectType::Projectile) && obj.get() != object)
        {
            vector2 save_obj_pos = obj->GetTransform().GetTranslation();

            if (player != nullptr)
            {
                if ((save_obj_pos.x >= min_pos.x) && (save_obj_pos.x <= max_pos.x) &&
                    (save_obj_pos.y >= min_pos.y) && (save_obj_pos.y <= max_pos.y))
                {
                    if (obj->GetObjectType() != ObjectType::Player)
                    {
                        capture_area_contian_object.push_back(obj.get());

                        obj->SetContainAreaCondition(true);
						obj->SetIsOutSideCondition(false);

                        if (!obj->IsDifferZoomSize())
                            original_scale.push_back(std::make_pair<vector2, Object*>(obj->GetTransform().GetScale(),
                                                                                      obj.get()));

                        result = true;
                    }
                    else
                    {
                        vector2 reset_min = {
                            reset_pos.x - player->GetTransform().GetScale().x / 2,
                            reset_pos.y - player->GetTransform().GetScale().x / 2
                        };
                        vector2 reset_max = {
                            reset_pos.x + player->GetTransform().GetScale().x / 2,
                            reset_pos.y + player->GetTransform().GetScale().x / 2
                        };

                        if ((save_obj_pos.x >= reset_max.x) || (save_obj_pos.x <= reset_min.x) ||
                            (save_obj_pos.y >= reset_max.y) || (save_obj_pos.y <= reset_min.y))
                        {
                            capture_area_contian_object.push_back(obj.get());

                            obj->SetContainAreaCondition(true);
							obj->SetIsOutSideCondition(false);

                            if (!obj->IsDifferZoomSize())
                                original_scale.push_back(std::make_pair<vector2, Object*>(
                                    obj->GetTransform().GetScale(),
                                    obj.get()));

                            result = true;
                        }
                    }
                }
                else if((min_pos.x >= save_obj_pos.x) || (min_pos.y >= save_obj_pos.y) ||
					(max_pos.x <= save_obj_pos.x) || (max_pos.y <= save_obj_pos.y))
                {
                    if (obj->IsContainArea())
                        SetOrigianlSize();

					obj->SetSlowModeCondition(false);

					obj->SetIsOutSideCondition(true);

                    obj->SetContainAreaCondition(false);
                }
            }
        }
		if (result)
		{
			return true;
		}

    }
    return false;
}

void Capture::Capturing()
{
    for (auto obj : capture_area_contian_object)
    {
        Object* temp = new Object(*obj);
        temp->GetComponentByTemplate<RigidBody>()->SetGravity(0);
        temp->GetComponentByTemplate<RigidBody>()->SetVelocity(0);
        temp->GetComponentByTemplate<Collision>()->ChangeCollisionBoxTranslation(temp->GetTransform().GetTranslation());

        if (m_c_filter == Filter::Jump)
        {
            temp->GetComponentByTemplate<Collision>()->SetFilter(Filter::Jump);
            temp->GetMesh().ChangeColor({0, 0, 255, 255});
        }
        if (m_c_filter == Filter::Speed)
        {
            temp->GetComponentByTemplate<Collision>()->SetFilter(Filter::Speed);
            temp->GetMesh().ChangeColor({0, 255, 0, 255});
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

        if (auto temp_collision = temp->GetComponentByTemplate<Collision>();
            temp_collision != nullptr)
        {
            temp_collision->SetIsGround(false);
        }

        if (obj->GetObjectType() == ObjectType::Player)
        {
            player->SetTranslation(reset_pos);
            player->GetComponentByTemplate<Collision>()->ChangeCollisionBoxTranslation(reset_pos);
            player->GetComponentByTemplate<Collision>()->SetIsGround(false);
			player->GetComponentByTemplate<Collision>()->SetIsCapobj(false);
        }

        temporary_obj_storage.push_back(temp);
        iscreate = true;
    }

}

void Capture::CreateCaptureObject()
{
    if (!temporary_obj_storage.empty())
    {
        for (auto obj : temporary_obj_storage)
        {
            Objectmanager_.AddObject(obj);
        }
    }

    if (!polaroid_object.empty())
    {
        for (auto obj : polaroid_object)
        {
            Objectmanager_.AddObject(obj->GetObject());
        }
    }

    temporary_obj_storage.clear();
    polaroid_object.clear();
}

void Capture::CreatePolaroidObject()
{
    if (iscreate)
    {
        for (auto obj : temporary_obj_storage)
        {
            Polaroid* temp = new Polaroid(obj);
            polaroid_object.push_back(temp);
        }
        iscreate = false;
    }
}

void Capture::CameraZoom()
{
    float zoom_ = static_cast<float>(Input::MouseWheelScroll());

    temp_zoom = zoom;

    if (zoom_ != 0)
    {
        if (zoom_ > 0)
        {
            if (zoom < zoom_max_value)
            {
                zoom += 0.05f;
            }

            if (zoom > zoom_max_value)
                zoom = zoom_max_value;
        }
        else if (zoom_ < 0)
        {
            if (zoom > zoom_min_value)
            {
                zoom -= 0.05f;
            }

            if (zoom < zoom_min_value)
                zoom = zoom_min_value;
        }
    }

    if (temp_zoom != zoom)
    {
        is_runtime_change = true;
    }
    else
    {
        is_runtime_change = false;
    }
}

void Capture::CameraZoomInOut()
{
    for (auto obj : Objectmanager_.GetObjectMap())
    {
		if ((obj->GetObjectType() == ObjectType::None || obj->GetObjectType() == ObjectType::Player ||
			obj->GetObjectType() == ObjectType::Projectile) && obj.get() != object)
		{
			if (!obj->IsOutSide())
			{
				if (!obj->IsDifferZoomSize())
				{
					vector2 scale = obj->GetTransform().GetScale();
					obj->SetScale(scale * zoom);

					if (auto temp_collision = obj->GetComponentByTemplate<Collision>();
						temp_collision != nullptr)
					{

						CollisionChangeZoomInOut(obj.get(), temp_collision);
                                            if(isCollisionSizeBig)
						temp_collision->ChangeCollisionBoxScale(obj->GetTransform().GetScale());
					}

					obj->SetZoomDifferCondition(true);
				}
				else
				{
					if (is_runtime_change)
					{
						for (auto size : original_scale)
						{
							if (obj.get() == size.second)
							{
								vector2 scale = size.first;
								obj->SetScale(scale * zoom);

								if (auto temp_collision = obj->GetComponentByTemplate<Collision>();
									temp_collision != nullptr)
								{
									CollisionChangeZoomInOut(obj.get(), temp_collision);
                                                                        if (isCollisionSizeBig)
									temp_collision->ChangeCollisionBoxScale(obj->GetTransform().GetScale());
								}
								obj->SetZoomDifferCondition(true);
							}
						}
					}
				}
			}
		}
    }
}

void Capture::SetOrigianlSize()
{
    for (auto obj : original_scale)
    {
		if(obj.second->IsOutSide())
		{
			obj.second->SetScale(obj.first);

			if (auto temp_collision = obj.second->GetComponentByTemplate<Collision>();
				temp_collision != nullptr)
			{
				if (temp_collision->GetIsGround() || temp_collision->GetIsCapobj())
				{
					vector2 translation = obj.second->GetTransform().GetTranslation();
					vector2 offset = (obj.second->GetTransform().GetScale() - temp_collision
						->GetCollisionTransform().GetScale()) / 2.0f;

					obj.second->GetTransform().SetTranslation({ translation.x, translation.y + offset.y });
				}
				temp_collision->ChangeCollisionBoxScale(obj.second->GetTransform().GetScale());
			}

			obj.second->SetZoomDifferCondition(false);
		}
    }
}

void Capture::ZoomObjectUpdate(float dt)
{
    float y_pos = object->GetTransform().GetScale().y - 60;
    float t = (zoom - zoom_min_value) / (zoom_max_value - zoom_min_value);

    t *= y_pos;

    vector2 base_translation = object->GetTransform().GetTranslation();
    vector2 base_scale = object->GetTransform().GetScale()/2.0f;

    zoombutton->SetTranslation({ base_translation.x + base_scale.x + 17, base_translation.y - base_scale.y + 30 + t});
}

void Capture::CollisionChangeZoomInOut(Object* obj, Collision* collision)
{
	if(collision->GetIsGround() || collision->GetIsCapobj())
	{
		vector2 translation = obj->GetTransform().GetTranslation();
		vector2 offset = (obj->GetTransform().GetScale() - collision->GetCollisionTransform().GetScale()) / 2.0f;

                if(isCollisionSizeBig)
                    obj->GetTransform().SetTranslation({ translation.x, translation.y + offset.y });
                else
                    collision->GetCollisionTransform().SetTranslation({ translation.x, translation.y + offset.y });
	}

	if(collision->GetIsLeft() || collision->GetIsLeftTile())
	{
		vector2 translation = obj->GetTransform().GetTranslation();
		vector2 offset = (obj->GetTransform().GetScale() - collision->GetCollisionTransform().GetScale()) / 2.0f;

                if (isCollisionSizeBig)
                    obj->GetTransform().SetTranslation({ translation.x + offset.x, translation.y });
                else
                collision->GetCollisionTransform().SetTranslation({ translation.x + offset.x, translation.y });
	}

	if (collision->GetIsRight() || collision->GetIsRightTile())
	{
		vector2 translation = obj->GetTransform().GetTranslation();
		vector2 offset = (obj->GetTransform().GetScale() - collision->GetCollisionTransform().GetScale()) / 2.0f;

                if (isCollisionSizeBig)
                    obj->GetTransform().SetTranslation({ translation.x - offset.x, translation.y });
                else
                collision->GetCollisionTransform().SetTranslation({ translation.x - offset.x, translation.y });
	}
}

void Capture::SlowMode()
{

	for (auto obj : capture_area_contian_object)
	{
		if(!obj->IsOutSide())
		{
			if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_RIGHT))
			{
				obj->SetSlowModeCondition(true);
			}
			if (Input::IsMouseReleased(GLFW_MOUSE_BUTTON_RIGHT))
			{

				obj->SetSlowModeCondition(false);
			}
		}
	}
}
