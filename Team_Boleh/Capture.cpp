#include "Capture.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include <iostream>
#include "State.hpp"
#include "Projectile.hpp"
#include "HUD.hpp"
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
        zoomobject->SetDepth(object->GetTransform().GetDepth());
        zoomobject->SetScale({ 30, size.y });
        zoomobject->SetObjectType(ObjectType::Capture_Camera);
        zoomobject->AddComponent(new Sprite("asset/images/zoom.png"));
		zoomobject->AddInitComponent(new Sound("asset/sounds/Camera_Capture.wav"));
		zoomobject->GetComponentByTemplate<Sound>()->AddSound("asset/sounds/Zoom_In.wav");
		zoomobject->GetComponentByTemplate<Sound>()->AddSound("asset/sounds/Zoom_Out.wav");

        zoombutton = new Object();
		zoombutton->SetTranslation({ object->GetTransform().GetTranslation().x + size.x / 1.8f , 
			object->GetTransform().GetTranslation().y - object->GetTransform().GetScale().y/2});
        zoombutton->SetMesh(mesh::CreateBox());
        zoombutton->SetDepth(object->GetTransform().GetDepth() - 0.1f);
        zoombutton->SetScale({ 30, 30 });
        zoombutton->SetObjectType(ObjectType::Capture_Camera);
        zoombutton->AddComponent(new Sprite("asset/images/zoom_button.png"));

		save_temp = object->GetTransform().GetTranslation().y - zoomobject->GetTransform().GetScale().y / 2;

        zoomobject->SetParent(&object->GetTransform());
		zoombutton->SetParent(&object->GetTransform());

        HUD_.Add_HUD_Object(zoomobject);
		HUD_.Add_HUD_Object(zoombutton);
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

	Capture_Camera_Move();

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
				zoomobject->GetComponentByTemplate<Sound>()->Play("asset/sounds/Camera_Capture.wav");
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
	object->SetTranslation(current_mouse_pos);
}

void Capture::SetVisibleCaptureObj()
{
	object->GetMesh().Visible();
	zoomobject->GetMesh().Visible();
	zoombutton->GetMesh().Visible();
	isvisible = true;
}

void Capture::SetInvisibleCaptureObj()
{
	object->GetMesh().Invisible();
	zoomobject->GetMesh().Invisible();
	zoombutton->GetMesh().Invisible();
	isvisible = false;
}

void Capture::SetZoomMinMax(float max, float min)
{
    zoom_max_value = max;
    zoom_min_value = min;
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
                            reset_pos.x - player->GetTransform().GetScale().x / 1.15f,
                            reset_pos.y - player->GetTransform().GetScale().x / 1.15f
                        };
                        vector2 reset_max = {
                            reset_pos.x + player->GetTransform().GetScale().x / 1.15f,
                            reset_pos.y + player->GetTransform().GetScale().x / 1.15f
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
        temp->GetComponentByTemplate<Collision>()->ChangeCollisionBoxScale(obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale());
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
            player->GetComponentByTemplate<Collision>()->ChangeCollisionBoxScale(player_scale);
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
				if(!AudioManager_.IsSFXPlaying())
					zoomobject->GetComponentByTemplate<Sound>()->Play("asset/sounds/Zoom_In.wav");

                zoom += 0.05f;
            }

            if (zoom > zoom_max_value)
                zoom = zoom_max_value;
        }
        else if (zoom_ < 0)
        {
            if (zoom > zoom_min_value)
            {
				if (!AudioManager_.IsSFXPlaying())
					zoomobject->GetComponentByTemplate<Sound>()->Play("asset/sounds/Zoom_Out.wav");

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
<<<<<<< HEAD
            if (!obj->IsOutSide())
            {
                if (!obj->IsDifferZoomSize())
                {
=======
                    if (!obj->IsOutSide())
                    {
                        if (!obj->IsDifferZoomSize())
                        {

                            if (auto temp_collision = obj->GetComponentByTemplate<Collision>();
                                temp_collision != nullptr)
                            {
                                CollisionChangeZoomInOut(obj.get(), temp_collision);
                                if (isCollisionSizeBig)
                                    temp_collision->ChangeCollisionBoxScale(obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale());
                            }
                            vector2 scale = obj->GetTransform().GetScale();
                            if (obj->GetComponentByTemplate<Collision>()->GetIsCelling())
                            {
                                if (const_zoom < zoom)
                                    obj->SetScale(scale * const_zoom);
                                else
                                    obj->SetScale(scale * zoom);
                            }
                            else
                                obj->SetScale(scale * zoom);
>>>>>>> d995f24ca99bfcb7d2fce22bb78c8b3d533ad7d6

                    if (auto temp_collision = obj->GetComponentByTemplate<Collision>();
                        temp_collision != nullptr)
                    {
                        CollisionChangeZoomInOut(obj.get(), temp_collision);
                        if (isCollisionSizeBig)
                            temp_collision->ChangeCollisionBoxScale(obj->GetTransform().GetScale());
                    }
                    vector2 scale = obj->GetTransform().GetScale();
                    if (obj->GetComponentByTemplate<Collision>()->GetIsCelling())
                    {
                        if (const_zoom < zoom)
                            obj->SetScale(scale * const_zoom);
                        else
                            obj->SetScale(scale * zoom);
                    }
                    else
                        obj->SetScale(scale * zoom);

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

                                if (auto temp_collision = obj->GetComponentByTemplate<Collision>();
                                    temp_collision != nullptr)
                                {
                                    CollisionChangeZoomInOut(obj.get(), temp_collision);
                                    if (isCollisionSizeBig)
                                        temp_collision->ChangeCollisionBoxScale(obj->GetTransform().GetScale());
                                }
                                vector2 scale = size.first;
                                if (obj->GetComponentByTemplate<Collision>()->GetIsCelling())
                                {
<<<<<<< HEAD
                                    if (const_zoom < zoom)
                                        obj->SetScale(scale * const_zoom);
                                    else
                                        obj->SetScale(scale * zoom);
=======
                                    if (obj.get() == size.second)
                                    {

                                        if (auto temp_collision = obj->GetComponentByTemplate<Collision>();
                                            temp_collision != nullptr)
                                        {
                                            CollisionChangeZoomInOut(obj.get(), temp_collision);
                                            if (isCollisionSizeBig)
                                                temp_collision->ChangeCollisionBoxScale(obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale());
                                        }
                                        vector2 scale = size.first;
                                        if (obj->GetComponentByTemplate<Collision>()->GetIsCelling())
                                        {
                                            if (const_zoom < zoom)
                                                obj->SetScale(scale * const_zoom);
                                            else
                                                obj->SetScale(scale * zoom);
                                        }
                                        else
                                            obj->SetScale(scale * zoom);

                                        obj->SetZoomDifferCondition(true);
                                    }
>>>>>>> d995f24ca99bfcb7d2fce22bb78c8b3d533ad7d6
                                }
                                else
                                    obj->SetScale(scale * zoom);

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

					//obj.second->GetTransform().SetTranslation({ translation.x, translation.y + offset.y });
				}
				temp_collision->ChangeCollisionBoxScale(obj.second->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale());
			}

			obj.second->SetZoomDifferCondition(false);
		}
    }
}

void Capture::ZoomObjectUpdate(float dt)
{

    float t = (zoom - zoom_min_value) / (zoom_max_value - zoom_min_value);
	float adding_pos = (object->GetTransform().GetTranslation().y + object->GetTransform().GetScale().y / 2) - (object->GetTransform().GetTranslation().y - object->GetTransform().GetScale().y / 2);

	adding_pos *= t;

	std::cout << adding_pos + save_temp << std::endl;

	zoombutton->SetSpecificPosition((adding_pos +save_temp) / object->GetTransform().GetScale().y);
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
        
        if(collision->GetIsCelling())
        {
            if(const_zoom == 0.f)
                const_zoom = zoom;
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
