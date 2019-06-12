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

    CameraZoomInOut();
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
    SetOrigianlSize(ground_obj, right_obj, left_obj);
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
	delete ground_obj;
	delete left_obj;
	delete right_obj;
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

                        if ((save_obj_pos.x >= reset_max.x) || (save_obj_pos.x <= reset_min.x) ||
                            (save_obj_pos.y >= reset_max.y) || (save_obj_pos.y <= reset_min.y))
                        {
                            capture_area_contian_object.push_back(obj.get());
                        }
                        obj->SetContainAreaCondition(true);
                        obj->SetIsOutSideCondition(false);
                        result = true;
                    }
                }
                else if ((min_pos.x >= save_obj_pos.x) || (min_pos.y >= save_obj_pos.y) ||
                    (max_pos.x <= save_obj_pos.x) || (max_pos.y <= save_obj_pos.y))
                {
                    obj->SetSlowModeCondition(false);
                    obj->SetIsOutSideCondition(true);
                    obj->SetContainAreaCondition(false);
                }
                original_scale.push_back(std::make_pair(obj->GetConstScaleSize(), obj.get()));
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
        temp->GetComponentByTemplate<Collision>()->ChangeCollisionBoxScale(
            obj->GetComponentByTemplate<Collision>()->GetCollisionTransform().GetScale());
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
    ground_obj = nullptr;
    left_obj = nullptr;
    right_obj = nullptr;
    for (auto obj : Objectmanager_.GetObjectMap())
    {
        if ((obj->GetObjectType() == ObjectType::None || obj->GetObjectType() == ObjectType::Player ||
            obj->GetObjectType() == ObjectType::Projectile) && obj.get() != object)
        {
            if (!obj->IsDifferentZoomSize())
            {
                if (!obj->IsOutSide())
                {
                    if (auto temp_collision = obj->GetComponentByTemplate<Collision>();
                        temp_collision != nullptr)
                    {
                        if (auto tile = Physics_.GroundCheck_return2(obj.get());
                            !tile.empty())
                        {
                            ground_obj = tile[0];

                            for (int i = 0; i < tile.size(); ++i)
                            {
                                if (ground_obj->GetTransform().GetTranslation().y < tile[i]->GetTransform().GetTranslation().y)
                                    ground_obj = tile[i];
                            }
                        }

                        if (auto tile = Physics_.GroundCheck_return_Right(obj.get());
                            !tile.empty())
                        {
                            right_obj = tile[0];

                            for (int i = 0; i < tile.size(); ++i)
                            {
                                if (right_obj->GetTransform().GetTranslation().x > tile[i]->GetTransform().GetTranslation().x)
                                    right_obj = tile[i];
                            }
                        }

                        if (auto tile = Physics_.GroundCheck_return_Left(obj.get());
                            !tile.empty())
                        {
                            left_obj = tile[0];

                            for (int i = 0; i < tile.size(); ++i)
                            {
                                if (left_obj->GetTransform().GetTranslation().x < tile[i]->GetTransform().GetTranslation().x)
                                    left_obj = tile[i];
                            }
                        }

                        temp_collision->ChangeCollisionBoxScale(temp_collision->GetConstCollisionScale() * zoom);
                        CollisionChangeZoomInOut_Ground(obj.get(), temp_collision, ground_obj, right_obj, left_obj);
                    }

                    for (auto original_size : original_scale)
                    {
                        if (original_size.second == obj.get())
                        {
                            vector2 size = original_size.first * zoom;
                            obj->SetScale(size);
                        }
                    }
                }
            }
        }
    }
}

void Capture::SetOrigianlSize(Object* ground, Object* right, Object* left)
{
    for (auto obj : original_scale)
    {
        if (obj.second->IsOutSide())
        {
            obj.second->SetScale(obj.first);

            if (auto temp_collision = obj.second->GetComponentByTemplate<Collision>();
                temp_collision != nullptr)
            {
                vector2 translation = obj.second->GetTransform().GetTranslation();
                vector2 offset = (temp_collision->GetCollisionTransform().GetScale() - temp_collision->GetConstCollisionScale());
                if ((temp_collision->GetIsLeft() || temp_collision->GetIsLeftTile()) && temp_collision->GetIsGround())
                {
                    if (left != nullptr)
                    {
                        float x_pos = left->GetTransform().GetTranslation().x;
                        float x_scale = left->GetTransform().GetScale().x / 2.0f;
                        float obj_scale_x = temp_collision->GetConstCollisionScale().x / 2.0f;
                        obj.second->SetTranslation({ x_pos + x_scale + obj_scale_x + 2.0f, translation.y - offset.y / 2.0f });
                    }
                }
                else if ((temp_collision->GetIsRight() || temp_collision->GetIsRightTile()) && temp_collision->GetIsGround())
                {
                    if (right != nullptr)
                    {
                        float x_pos = right->GetTransform().GetTranslation().x;
                        float x_scale = right->GetTransform().GetScale().x / 2.0f;
                        float obj_scale_x = temp_collision->GetConstCollisionScale().x / 2.0f;
                        obj.second->SetTranslation({ x_pos - x_scale - obj_scale_x - 2.0f, translation.y - offset.y / 2.0f });
                    }

                }
                else if (temp_collision->GetIsGround() || temp_collision->GetisGet())
                {
                    obj.second->SetSpecificPosition(translation.y - offset.y / 2.0f);
                }
                temp_collision->ChangeCollisionBoxScale(temp_collision->GetConstCollisionScale());
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

void Capture::CollisionChangeZoomInOut_Ground(Object* obj, Collision* collision, Object* ground, Object* right, Object* left)
{
    vector2 translation = obj->GetTransform().GetTranslation();

    if (ground != nullptr)
    {
        float y_pos = ground->GetTransform().GetTranslation().y;
        float y_scale_y = ground->GetTransform().GetScale().y / 2.0f;
        float obj_scale_y = collision->GetCollisionTransform().GetScale().y / 2.0f;

        if ((collision->GetIsGround() || collision->GetisGet()) && (collision->GetIsLeft() || collision->GetIsLeftTile()))
        {
            if (left != nullptr)
            {
                float x_pos = left->GetTransform().GetTranslation().x;
                float x_scale = left->GetTransform().GetScale().x / 2.0f;
                float obj_scale_x = collision->GetCollisionTransform().GetScale().x / 2.0f;
                obj->SetTranslation({ x_pos + x_scale + obj_scale_x + 2.0f, y_pos + y_scale_y + obj_scale_y });
            }
        }
        else if ((collision->GetIsGround() || collision->GetisGet()) && (collision->GetIsRight() || collision->GetIsRightTile()))
        {
            if (right != nullptr)
            {
                float x_pos = right->GetTransform().GetTranslation().x;
                float x_scale = right->GetTransform().GetScale().x / 2.0f;
                float obj_scale_x = collision->GetCollisionTransform().GetScale().x / 2.0f;
                obj->SetTranslation({ x_pos - x_scale - obj_scale_x - 2.0f, y_pos + y_scale_y + obj_scale_y });
            }

        }
        else if (collision->GetIsGround() || collision->GetisGet())
        {
            obj->SetSpecificPosition(y_pos + y_scale_y + obj_scale_y);
        }
    }

    //float distance = abs((obj->GetTransform().GetTranslation().y - obj_scale_y) - (y_pos + y_scale_y));
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
