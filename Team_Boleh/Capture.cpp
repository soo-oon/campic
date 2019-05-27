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
        zoomobject->SetTranslation({ object->GetTransform().GetTranslation().x, object->GetTransform().GetTranslation().y - size.y/2 + 20});
        zoomobject->SetDepth(object->GetTransform().GetDepth());
        zoomobject->SetScale({ 260, 30 });
        zoomobject->SetObjectType(ObjectType::Capture_Camera);
        zoomobject->AddComponent(new Sprite("asset/images/Objects/ZoomLevel.png"));
		zoomobject->AddInitComponent(new Sound("asset/sounds/Camera_Capture.wav"));
		zoomobject->GetComponentByTemplate<Sound>()->AddSound("asset/sounds/Zoom_In.wav");
		zoomobject->GetComponentByTemplate<Sound>()->AddSound("asset/sounds/Zoom_Out.wav");
		temp_local_bar_scale = zoomobject->GetTransform().GetScale();

		zoombutton = new Object();
		zoombutton->SetTranslation({object->GetTransform().GetTranslation().x+2.5f, object->GetTransform().GetTranslation().y - size.y/2 + 35});
		zoombutton->SetMesh(mesh::CreateBox());
		zoombutton->SetDepth(object->GetTransform().GetDepth() - 0.1f);
        zoombutton->SetScale({ 25, 30 });
        zoombutton->SetObjectType(ObjectType::Capture_Camera);
        zoombutton->AddComponent(new Sprite("asset/images/Objects/ZoomDial.png"));

		zoomobject->SetParent(&object->GetTransform());
		zoombutton->SetParent(&object->GetTransform());

		Objectmanager_.AddObject(zoomobject);
		Objectmanager_.AddObject(zoombutton);
	}

	const_zoom = zoom;
	zoom_min_value = 0.5f;
	zoom_max_value = 2.5f;

	return true;
}

void Capture::Update(float dt)
{
	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_MIDDLE))
		zoom = 1.0f;

	CameraZoom();
	ZoomObjectUpdate(dt);
	CaptureObjectMove();

	if (player == nullptr)
	{
		player = StateManager_.GetCurrentState()->GetPlayerObjectPointer();
	}

	if (Input::IsKeyTriggered(GLFW_KEY_KP_3))
		isCollisionSizeBig = true;
	if (Input::IsKeyTriggered(GLFW_KEY_KP_6))
		isCollisionSizeBig = false;

	if (IsCaptureArea())
	{
		if (StateManager_.GetCurrentState()->GetCaptureLimit() > 0)
		{
			if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
			{
				StateManager_.GetCurrentState()->AddDataCount();
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

void Capture::CaptureObjectMove()
{
	vector2 mouse_pos = Input::GetMousePos();
	Player* player = StateManager_.GetCurrentState()->GetPlayerObjectPointer()->GetComponentByTemplate<Player>();

	vector2 check = object->GetTransform().GetTranslation();

	if (player->GetMouseOffset().x != 0 || player->GetMouseOffset().y != 0)
	{
		object->SetTranslation(mouse_pos + player->GetMouseOffset());
	}
	else
	{
		object->SetTranslation(mouse_pos);
	}

	if (player->GetMouseOffset().x != 0 || player->GetMouseOffset().y != 0)
	{
		if (abs(check.x - object->GetTransform().GetTranslation().x) > 50 || abs(check.y - object->GetTransform().GetTranslation().y) > 50)
		{
			object->GetTransform().SetTranslation(check);
		}
	}
}

void Capture::SetZoomMaxMin(float max, float min)
{
	if(min != 0.0f)
		zoom_min_value = min;

	zoom_max_value = max;
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
				else if ((min_pos.x >= save_obj_pos.x) || (min_pos.y >= save_obj_pos.y) ||
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
		if (temp->GetComponentByTemplate<RigidBody>())
		{
			temp->GetComponentByTemplate<RigidBody>()->SetGravity(0);
			temp->GetComponentByTemplate<RigidBody>()->SetVelocity(0);
		}
		if (temp->GetComponentByTemplate<Collision>()) {
			temp->GetComponentByTemplate<Collision>()->ChangeCollisionBoxScale(
				obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale());
			temp->GetComponentByTemplate<Collision>()->ChangeCollisionBoxTranslation(temp->GetTransform().GetTranslation());
		}

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
                        player->GetComponentByTemplate<RigidBody>()->SetVelocity(0);
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

	//std::cout << zoom << std::endl;

	if(zoom_ != 0)
	{
		if(zoom == 1.0f && zoom_ > 0)
		{
			zoomobject->GetComponentByTemplate<Sound>()->Play("asset/sounds/Zoom_In.wav");
			float temp = zoom_max_value - const_zoom;
			float t = temp / 3.0f;
			zoom += t;

		}
		else if(zoom == 1.0f && zoom_ < 0)
		{
			zoomobject->GetComponentByTemplate<Sound>()->Play("asset/sounds/Zoom_In.wav");
			float temp = 1.0f - zoom_min_value;
			float t = temp / 3.0f;
			zoom -= t;
		}
		else
		{
			if (zoom_ > 0)
			{
				if (zoom > 1.0f)
				{
					zoomobject->GetComponentByTemplate<Sound>()->Play("asset/sounds/Zoom_In.wav");
					float temp = zoom_max_value - const_zoom;
					float t = temp / 3.0f;
					zoom += t;
				}
				else
				{
					zoomobject->GetComponentByTemplate<Sound>()->Play("asset/sounds/Zoom_In.wav");
					float temp = 1.0f - zoom_min_value;
					float t = temp / 3.0f;
					zoom += t;
				}

				if (zoom > zoom_max_value)
				{
					zoom = zoom_max_value;
				}
			}
			else if(zoom_ < 0)
			{
				if (zoom > 1.0f)
				{
					zoomobject->GetComponentByTemplate<Sound>()->Play("asset/sounds/Zoom_In.wav");
					float temp = zoom_max_value - const_zoom;
					float t = temp / 3.0f;
					zoom -= t;
				}
				else
				{
					zoomobject->GetComponentByTemplate<Sound>()->Play("asset/sounds/Zoom_In.wav");
					float temp = 1.0f - zoom_min_value;
					float t = temp / 3.0f;
					zoom -= t;
				}

				if (zoom < zoom_min_value)
				{
					zoom = zoom_min_value;
				}
			}
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
					if (!obj->IsOutSide())
					{
						if (!obj->IsDifferZoomSize())
						{
							if (auto temp_collision = obj->GetComponentByTemplate<Collision>();
								temp_collision != nullptr)
							{
								CollisionChangeZoomInOut(obj.get(), temp_collision);
								if (isCollisionSizeBig)
									temp_collision->ChangeCollisionBoxScale(
										obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale());
							}
							vector2 scale = obj->GetTransform().GetScale();
							if (obj->GetComponentByTemplate<Collision>() != nullptr)
							{
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
											if (const_zoom < zoom)
												obj->SetScale(scale * const_zoom);
											else
												obj->SetScale(scale * zoom);
											if (obj.get() == size.second)
											{
												if (auto temp_collision = obj->GetComponentByTemplate<Collision>();
													temp_collision != nullptr)
												{
													CollisionChangeZoomInOut(obj.get(), temp_collision);
													if (isCollisionSizeBig)
														temp_collision->ChangeCollisionBoxScale(
															obj->GetComponentByTemplate<Collision>()->
															     GetCollisionTransform().GetScale());
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
	}
}

void Capture::SetOrigianlSize()
{
	for (auto obj : original_scale)
	{
            if ((obj.second->GetObjectType() == ObjectType::None || obj.second->GetObjectType() == ObjectType::Player ||
                obj.second->GetObjectType() == ObjectType::Projectile))
            {
                if (obj.second->IsOutSide())
                {
                    obj.second->SetScale(obj.first);

                    if (auto temp_collision = obj.second->GetComponentByTemplate<Collision>();
                        temp_collision != nullptr)
                    {
                        if (temp_collision->GetIsGround() || temp_collision->GetIsCapobj())
                        {
                            vector2 translation = obj.second->GetTransform().GetTranslation();
                            vector2 offset = (obj.second->GetTransform().GetScale() - temp_collision
                                ->GetCollisionTransform().
                                GetScale()) / 2.0f;

                        }
                        temp_collision->ChangeCollisionBoxScale(
                            obj.second->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale());
                    }

                    obj.second->SetZoomDifferCondition(false);
                }
            }
	}
}

void Capture::ZoomObjectUpdate(float dt)
{
	float t = 0.0f;
	float half_scale = temp_local_bar_scale.x/2.0f;
	float temp_scale = 0.0f;

	if(zoom > 1.0f)
	{
		t = (zoom - 1.0f) / (zoom_max_value - 1.0f);
		temp_scale = half_scale * t;
		zoombutton->SetSpecificPosition((2.5f +temp_scale) / object->GetTransform().GetScale().x, true);
	}
	else if(zoom < 1.0f)
	{
		t = (zoom - zoom_min_value) / (1.0f - zoom_min_value);
		temp_scale = half_scale * t;
		zoombutton->SetSpecificPosition((2.5f -(half_scale - temp_scale)) / object->GetTransform().GetScale().x, true);

	}
	else if(zoom == 1.0f)
	{
		zoombutton->SetSpecificPosition(2.5f / object->GetTransform().GetScale().x, true);
	}
}

void Capture::CollisionChangeZoomInOut(Object* obj, Collision* collision)
{
	if (collision->GetIsGround() || collision->GetIsCapobj())
	{
		vector2 translation = obj->GetTransform().GetTranslation();
		vector2 offset = (obj->GetTransform().GetScale() - collision->GetCollisionTransform().GetScale()) /
			2.0f;

		if (isCollisionSizeBig)
			obj->GetTransform().SetTranslation({translation.x, translation.y + offset.y});
		else
			collision->GetCollisionTransform().SetTranslation({translation.x, translation.y + offset.y});
	}

	if (collision->GetIsLeft() || collision->GetIsLeftTile())
	{
		vector2 translation = obj->GetTransform().GetTranslation();
		vector2 offset = (obj->GetTransform().GetScale() - collision->GetCollisionTransform().GetScale()) /
			2.0f;

		if (isCollisionSizeBig)
			obj->GetTransform().SetTranslation({translation.x + offset.x, translation.y});
		else
			collision->GetCollisionTransform().SetTranslation({translation.x + offset.x, translation.y});
	}

	if (collision->GetIsRight() || collision->GetIsRightTile())
	{
		vector2 translation = obj->GetTransform().GetTranslation();
		vector2 offset = (obj->GetTransform().GetScale() - collision->GetCollisionTransform().GetScale()) /
			2.0f;

		if (isCollisionSizeBig)
			obj->GetTransform().SetTranslation({translation.x - offset.x, translation.y});
		else
			collision->GetCollisionTransform().SetTranslation({translation.x - offset.x, translation.y});
	}

	if (collision->GetIsCelling())
	{
		if (const_zoom == 0.f)
			const_zoom = zoom;
	}
}

void Capture::SlowMode()
{
	for (auto obj : capture_area_contian_object)
	{
		if (!obj->IsOutSide())
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
