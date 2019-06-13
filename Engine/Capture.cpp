#include "Capture.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include "State.hpp"
#include "HUD.hpp"
#include "Player.hpp"
#include "Physics.hpp"
#include <iostream>

bool Capture::Initialize(Object* Ob)
{
	if (object == nullptr)
	{
		object = Ob;

		vector2 size = object->GetTransform().GetScale();
		zoomobject = new Object();
		zoomobject->SetMesh(mesh::CreateBox());
		zoomobject->SetTranslation({
			object->GetTransform().GetTranslation().x, object->GetTransform().GetTranslation().y - size.y / 2 + 20
		});
		zoomobject->SetDepth(object->GetTransform().GetDepth());
		zoomobject->SetScale({260, 30});
		zoomobject->SetObjectType(ObjectType::Capture_Camera);
		zoomobject->AddComponent(new Sprite("asset/images/Objects/ZoomLevel.png"));
		zoomobject->AddInitComponent(new Sound("asset/sounds/Camera_Capture.wav"));
		zoomobject->GetComponentByTemplate<Sound>()->AddSound("asset/sounds/Zoom_In.wav");
		zoomobject->GetComponentByTemplate<Sound>()->AddSound("asset/sounds/Zoom_Out.wav");
		temp_local_bar_scale = zoomobject->GetTransform().GetScale();

		zoombutton = new Object();
		zoombutton->SetTranslation({
			object->GetTransform().GetTranslation().x + 2.5f,
			object->GetTransform().GetTranslation().y - size.y / 2 + 35
		});
		zoombutton->SetMesh(mesh::CreateBox());
		zoombutton->SetDepth(object->GetTransform().GetDepth() - 0.1f);
		zoombutton->SetScale({25, 30});
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
	is_change_capture_count = true;

	return true;
}

void Capture::Update(float dt)
{
	if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_MIDDLE))
		zoom = 1.0f;

	//std::cout << "Mouse Pos: " << Input::GetMousePos();
	/*if(save_ground_obj != nullptr)
		std::cout << "Ground Pos: " << save_ground_obj->GetTransform().GetTranslation();*/
	
	CameraZoom();
	ZoomObjectUpdate(dt);
	CaptureObjectMove();

	if (player == nullptr)
	{
		player = StateManager_.GetCurrentState()->GetPlayerObjectPointer();
	}
	else
	{
		if (player->GetComponentByTemplate<Collision>()->GetShouldRestartPos())
		{
			player->SetTranslation(reset_pos);
			player->GetComponentByTemplate<Collision>()->SetShouldRestartPos(false);
			return;
		}

	}

	if (Input::IsKeyTriggered(GLFW_KEY_KP_3))
		isCollisionSizeBig = true;
	if (Input::IsKeyTriggered(GLFW_KEY_KP_6))
		isCollisionSizeBig = false;

	CameraZoomInOut();
	if (IsCaptureArea())
	{
		if (StateManager_.GetCurrentState()->GetCaptureLimit() > 0)
		{
			if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
			{
				StateManager_.GetCurrentState()->AddDataCount();
				--StateManager_.GetCurrentState()->GetCaptureLimit();
				cheese = true;
				is_change_capture_count = true;
				Capturing();
				CreatePolaroidObject();
				CreateCaptureObject();
				zoomobject->GetComponentByTemplate<Sound>()->Play("asset/sounds/Camera_Capture.wav");
			}
		}
	}
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
	delete zoombutton;
	delete zoomobject;
	delete player;
	delete ground_object;
	delete left_object;
	delete right_object;
	delete cap_ground_obj;

	original_scale.clear();
	capture_area_contian_object.clear();
	temporary_obj_storage.clear();
	polaroid_object.clear();
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
		if (abs(check.x - object->GetTransform().GetTranslation().x) > 50 || abs(
			check.y - object->GetTransform().GetTranslation().y) > 50)
		{
			object->GetTransform().SetTranslation(check);
		}
	}
}

void Capture::SetZoomMaxMin(float max, float min)
{
	if (min != 0.0f)
		zoom_min_value = min;

	zoom_max_value = max;
}

bool Capture::IsCaptureArea()
{
	bool result = false;
	capture_area_contian_object.clear();
	original_scale.clear();

	vector2 object_pos = object->GetTransform().GetTranslation();
	vector2 object_size = object->GetTransform().GetScale() / 2;
	vector2 min_pos = {object_pos.x - object_size.x, object_pos.y - object_size.y};
	vector2 max_pos = {object_pos.x + object_size.x, object_pos.y + object_size.y};

	for (auto& obj : Objectmanager_.GetObjectMap())
	{
		if ((obj->GetObjectType() == ObjectType::None || obj->GetObjectType() == ObjectType::Player ||
			obj->GetObjectType() == ObjectType::Projectile) && obj.get() != object)
		{
			if (auto obj_collision = obj->GetComponentByTemplate<Collision>();
				obj_collision != nullptr)
			{
				vector2 save_min_obj = { obj_collision->GetCollisionTransform().GetTranslation().x - obj_collision->GetCollisionTransform().GetScale().x / 2.0f,
				obj_collision->GetCollisionTransform().GetTranslation().y - obj_collision->GetCollisionTransform().GetScale().y / 2.0f };

				vector2 save_max_obj = { obj_collision->GetCollisionTransform().GetTranslation().x + obj_collision->GetCollisionTransform().GetScale().x / 2.0f,
				obj_collision->GetCollisionTransform().GetTranslation().y + obj_collision->GetCollisionTransform().GetScale().y / 2.0f };

				if (player != nullptr)
				{
					if ((save_min_obj.x >= min_pos.x) && (save_max_obj.x <= max_pos.x) &&
						(save_min_obj.y >= min_pos.y) && (save_max_obj.y <= max_pos.y))
					{
						if (obj->GetObjectType() != ObjectType::Player)
						{
							capture_area_contian_object.push_back(obj.get());

							obj->SetContainAreaCondition(true);
							obj->SetIsOutSideCondition(false);

							result = true;
						}
						else
						{
							vector2 reset_min;
							vector2 reset_max;

							if (auto collsion = player->GetComponentByTemplate<Collision>();
								collsion != nullptr)
							{
								reset_min = {
									reset_pos.x - collsion->GetCollisionTransform().GetScale().x,
									reset_pos.y - collsion->GetCollisionTransform().GetScale().y
								};

								reset_max = {
									reset_pos.x + collsion->GetCollisionTransform().GetScale().x,
									reset_pos.y + collsion->GetCollisionTransform().GetScale().y
								};
							}

							if ((save_max_obj.x >= reset_max.x) || (save_min_obj.x <= reset_min.x) ||
								(save_max_obj.y >= reset_max.y) || (save_min_obj.y <= reset_min.y))
							{
								capture_area_contian_object.push_back(obj.get());
							}
							obj->SetContainAreaCondition(true);
							obj->SetIsOutSideCondition(false);
							result = true;
						}
					}
					else if ((min_pos.x >= save_max_obj.x) || (min_pos.y >= save_max_obj.y) ||
						(max_pos.x <= save_min_obj.x) || (max_pos.y <= save_min_obj.y))
					{
						obj->SetSlowModeCondition(false);
						obj->SetIsOutSideCondition(true);
						obj->SetIsChangePosition(false);
						obj->SetContainAreaCondition(false);
					}
					original_scale.push_back(std::make_pair(obj->GetConstScaleSize(), obj.get()));
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
		vector2 reset_max = reset_pos + vector2{ 75,75 };
		vector2 reset_min = reset_pos - vector2{ 75,75 };
		vector2 max = obj->GetTransform().GetTranslation() + obj->GetTransform().GetScale()/2.0f;
		vector2 min = obj->GetTransform().GetTranslation() - obj->GetTransform().GetScale()/2.0f;

		//std::cout << reset_pos;

		if(Physics_.IntersectionCheckAABBPositionBase(reset_min, reset_max, min, max))
		{
			std::cout << "hi" << std::endl;
			continue;
		}

		Object* temp = new Object(*obj);
		temp->GetComponentByTemplate<RigidBody>()->SetGravity(0);
		if(zoom < 1.0f)
		{
			temp->GetComponentByTemplate<Collision>()->ChangeCollisionBoxScale(
				obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale());
		}
		else
		{
			temp->GetComponentByTemplate<Collision>()->ChangeCollisionBoxScale(
				obj->GetComponentByTemplate<Collision>()->GetConstCollisionScale() * zoom);
		}
		
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
			Physics::capture_ground_obj = nullptr;

		}

		temporary_obj_storage.push_back(std::make_pair(temp, obj->GetTransform().GetScale()));
		iscreate = true;
	}
}

void Capture::CreateCaptureObject()
{
	if (!temporary_obj_storage.empty())
	{
		for (auto obj : temporary_obj_storage)
		{
			Objectmanager_.AddObject(obj.first);
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
			Polaroid* temp = new Polaroid(obj.first, obj.second);
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
		if (zoom == 1.0f && zoom_ > 0)
		{
			zoomobject->GetComponentByTemplate<Sound>()->Play("asset/sounds/Zoom_In.wav");
			float temp = zoom_max_value - const_zoom;
			float t = temp / 3.0f;
			zoom += t;
		}
		else if (zoom == 1.0f && zoom_ < 0)
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
			else if (zoom_ < 0)
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
	ground_object = nullptr;
	left_object = nullptr;
	right_object = nullptr;
	cap_ground_obj = nullptr;

	for (auto obj : Objectmanager_.GetObjectMap())
	{
		if ((obj->GetObjectType() == ObjectType::None || obj->GetObjectType() == ObjectType::Player ||
			obj->GetObjectType() == ObjectType::Projectile) && obj.get() != object)
		{
			if (!obj->IsOutSide())
			{
				obj->GetTransform().SetScale(obj->GetConstScaleSize() * zoom);

				auto ground_objects = Physics_.GroundCheck_return(obj.get());
				auto left_objects = Physics_.Return_Left_Collision(obj.get());
				auto right_objects = Physics_.Return_Right_Collision(obj.get());
				if(!ground_objects.empty())
				{
					ground_object = ground_objects[0];

					for (auto ground_obj : ground_objects)
					{
						if (ground_obj->GetTransform().GetTranslation().y > ground_object->GetTransform().GetTranslation().y)
							ground_object = ground_obj;
					}	
				}

				if (ground_object != nullptr)
				{
					if (!left_objects.empty())
					{
						left_object = left_objects[0];

						for (auto left_obj : left_objects)
						{
							float test_position = ground_object->GetTransform().GetTranslation().y;
							if (left_obj->GetTransform().GetTranslation().y > test_position)
							{
								if (left_obj->GetTransform().GetTranslation().x > left_object->GetTransform().GetTranslation().x)
									left_object = left_obj;
							}
						}
					}

					if (!right_objects.empty())
					{
						right_object = right_objects[0];

						for (auto right_obj : right_objects)
						{
							float test_position = ground_object->GetTransform().GetTranslation().y;
							if (right_obj->GetTransform().GetTranslation().y > test_position)
							{
								if (right_obj->GetTransform().GetTranslation().x < right_object->GetTransform().GetTranslation().x)
									right_object = right_obj;
							}
						}
					}
				}

				if (ground_object != nullptr)
					save_ground_obj = ground_object;

				if (left_object != nullptr)
					save_left_obj = left_object;

				if (right_object != nullptr)
					save_right_obj = right_object;

				if (ground_object != nullptr || Physics::capture_ground_obj != nullptr)
				{

					if (auto temp_collision = obj->GetComponentByTemplate<Collision>();
						temp_collision != nullptr)
					{
						float y_pos = 0.0f;

						if (temp_collision->GetIsCapobj())
							y_pos = Physics::capture_ground_obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetTranslation().y
							+ Physics::capture_ground_obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale().y / 2.0f;
						else if (temp_collision->GetIsGround())
							y_pos = save_ground_obj->GetTransform().GetTranslation().y + ground_object->GetTransform().GetScale().y / 2.0f;

						if(zoom < 1.0f)
							temp_collision->SetCollisionScale(temp_collision->GetConstCollisionScale() * zoom);
						else
							temp_collision->SetCollisionScale(temp_collision->GetConstCollisionScale());

						if (temp_collision->GetIsGround() || temp_collision->GetIsCapobj())
						{
							obj->SetChangeCollisionBox(true, y_pos + temp_collision->GetCollisionTransform().GetScale().y / 2.0f);

							if(zoom > 1.0f)
							{
								obj->SetIsChangePosition(true,y_pos + obj->GetTransform().GetScale().y / 2.0f -8.0f);
							}
							else if(zoom == 1.0f)
							{
								obj->SetIsChangePosition(true, y_pos + temp_collision->GetCollisionTransform().GetScale().y / 2.0f);

							}
							else
							{
								obj->SetIsChangePosition(true,y_pos + temp_collision->GetCollisionTransform().GetScale().y / 2.0f);
							}

						}
						else
						{
							obj->SetIsChangePosition(false);
							temp_collision->SetIsFollow(true, 0);
						}
					}
				}
				else
				{
					if(auto temp_collision = obj->GetComponentByTemplate<Collision>();
						temp_collision != nullptr)
					{
						temp_collision->SetIsGround(false);
						temp_collision->SetIsFollow(true, 0);
					}
					obj->SetIsChangePosition(false);

				}

			}
			else
			{
				if (auto temp_collision = obj->GetComponentByTemplate<Collision>();
					temp_collision != nullptr)
				{
					temp_collision->SetIsFollow(true, 0);
					obj->SetIsChangePosition(false);
				}
			}
		}
	}
}

void Capture::SetOrigianlSize()
{
	for (auto obj : original_scale)
	{
		if (obj.second->IsOutSide())
		{
			obj.second->SetScale(obj.second->GetConstScaleSize());

			if(auto temp_collision = obj.second->GetComponentByTemplate<Collision>();
				temp_collision != nullptr)
			{
				float y_pos = 0.0f;
				if (save_ground_obj != nullptr || cap_ground_obj != nullptr)
				{
					if (Physics::capture_ground_obj != nullptr)
					{
						y_pos = Physics::capture_ground_obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetTranslation().y
							+ Physics::capture_ground_obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale().y / 2.0f
							+ temp_collision->GetConstCollisionScale().y / 2.0f;
					}
					else if (temp_collision->GetIsGround())
					{
						y_pos = save_ground_obj->GetTransform().GetTranslation().y
							+ save_ground_obj->GetTransform().GetScale().y / 2.0f
							+ temp_collision->GetConstCollisionScale().y / 2.0f;
					}

					if (zoom < 1.0f)
					{
						temp_collision->SetCollisionScale(temp_collision->GetConstCollisionScale());

						if(Physics::capture_left_obj!= nullptr)
						{
							float x_pos = Physics::capture_left_obj->GetTransform().GetTranslation().x
								+ Physics::capture_left_obj->GetTransform().GetScale().x / 2.0f
								+ temp_collision->GetConstCollisionScale().x / 2.0f;

							obj.second->SetSpecificPosition(x_pos, true);
							obj.second->SetChangeCollisionBox(true, x_pos, true);
							obj.second->SetIsChangePosition(false);
						}
						else if(Physics::capture_right_obj!= nullptr)
						{
							float x_pos = Physics::capture_right_obj->GetTransform().GetTranslation().x
								- Physics::capture_right_obj->GetTransform().GetScale().x / 2.0f
								- temp_collision->GetConstCollisionScale().x / 2.0f;
							obj.second->SetSpecificPosition(x_pos, true);
							obj.second->SetChangeCollisionBox(true, x_pos, true);

							obj.second->SetIsChangePosition(false);
						}
						else if (temp_collision->GetIsLeftTile())
						{
							float x_pos = save_left_obj->GetTransform().GetTranslation().x
								+ save_left_obj->GetTransform().GetScale().x / 2.0f
								+ temp_collision->GetConstCollisionScale().x / 2.0f;

							obj.second->SetSpecificPosition( x_pos, true);
							obj.second->SetChangeCollisionBox(true, x_pos, true);
							obj.second->SetIsChangePosition(false);
						}
						else if(temp_collision->GetIsRightTile())
						{
							float x_pos = save_right_obj->GetTransform().GetTranslation().x
							   - save_right_obj->GetTransform().GetScale().x / 2.0f
								- temp_collision->GetConstCollisionScale().x / 2.0f;
							obj.second->SetSpecificPosition(x_pos, true);
							obj.second->SetChangeCollisionBox(true, x_pos, true);

							obj.second->SetIsChangePosition(false);
						}
						/*if(temp_collision->GetIsGround() || temp_collision->GetIsCapobj())
						{
							obj.second->SetSpecificPosition(y_pos);
							obj.second->SetChangeCollisionBox(true, y_pos);

							obj.second->SetIsChangePosition(false);

						}*/
					}
					if (temp_collision->GetIsGround() || temp_collision->GetIsCapobj())
					{
						obj.second->SetSpecificPosition(y_pos);
						obj.second->SetChangeCollisionBox(true, y_pos);

						obj.second->SetIsChangePosition(false);

					}
				}
			}
		}
	}
}

void Capture::ZoomObjectUpdate(float dt)
{
	float t = 0.0f;
	float half_scale = temp_local_bar_scale.x / 2.0f;
	float temp_scale = 0.0f;

	if (zoom > 1.0f)
	{
		t = (zoom - 1.0f) / (zoom_max_value - 1.0f);
		temp_scale = half_scale * t;
		zoombutton->SetSpecificPosition((2.5f + temp_scale) / object->GetTransform().GetScale().x, true);
	}
	else if (zoom < 1.0f)
	{
		t = (zoom - zoom_min_value) / (1.0f - zoom_min_value);
		temp_scale = half_scale * t;
		zoombutton->SetSpecificPosition((2.5f - (half_scale - temp_scale)) / object->GetTransform().GetScale().x, true);
	}
	else if (zoom == 1.0f)
	{
		zoombutton->SetSpecificPosition(2.5f / object->GetTransform().GetScale().x, true);
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
