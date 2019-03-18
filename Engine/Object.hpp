/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Object.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include <vector>
#include "Component.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "Collision.hpp"
#include "Camera.hpp"
#include "RigidBody.hpp"
#include "Sound.hpp"

enum class ObjectType {
    Player,
    Wall,
    Door,
    Item_Static,
    Item_Dynamic,
    Camera,
    None,
}; 

class Object
{
public:
    void AddComponent(Component* component);
    void Add_Init_Component(Component* component);

public:
    void SetMesh(Mesh mesh);
    void SetTranslation(const vector2& position);
    void SetScale(const vector2& scale);
    void SetRotation(const float& rotation);
    void SetDepth(const float& depth);
	void SetParent(const Transform* transform_);
    void SetGravity(float gravity_own);
	void Set_HUD_Object_Size(const vector2 size) { HUD_Object_size = size; }
    void SetObjectType(ObjectType obj_type) { object_type = obj_type; }
    void SetSpeed(float speed_) { speed = speed_; }
    void SetObjectDead() { isDead = true; }

    // Update
    //if (hp <= 0)
    //    is_alive = false;

public:
    ObjectType GetObjectType() { return object_type; }
	std::vector<Component*> GetComponent() { return components; }
	vector2 Get_Object_HUD_Size() { return HUD_Object_size; }
    float GetGravity();
    Mesh& GetMesh();
    Transform& GetTransform();
    float GetSpeed() { return speed; }
    int GetDamage() { return attack_damage; }
    int GetHp() { return hp; }

    template <typename COMPONENT>
    COMPONENT* GetComponentByTemplate() const;

public:
    bool IsDead() { return isDead; }

public:
	std::string texture_path = "no_texture";
	int object_id = 0;
	int component_type_id = 0;

private:
    Mesh object_mesh{};
    Transform transform{};
	vector2 HUD_Object_size{};
    std::vector<Component*> components;
    ObjectType object_type = ObjectType::None;

private:
    float gravity = 1;
    int hp = 5;
    int attack_damage = 1;
    float speed = 1;
    bool isDead = false;
};

template <typename COMPONENT>
COMPONENT* Object::GetComponentByTemplate() const
{
    for (auto i : components)
    {
        if (typeid(COMPONENT) == typeid(*i))
        {
            return dynamic_cast<COMPONENT*>(i);
        }
    }
    return nullptr;
}
