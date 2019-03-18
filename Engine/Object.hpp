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

enum class Object_Draw_Type
{
	None, Sprite, Animation, Particle, Collision, Camera, Font
};

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
	Object(Object_Draw_Type type) : m_draw_type(type)
	{}
    void AddComponent(Component* component);
    void AddInitComponent(Component* component);


public:
    void SetMesh(Mesh mesh);
    void SetTranslation(const vector2& position);
    void SetScale(const vector2& scale);
    void SetRotation(const float& rotation);
    void SetDepth(const float& depth);
	void SetParent(const Transform* transform_);
	void SetObjectDrawType(Object_Draw_Type type);
	void SetIsDead(bool condition);

public:
	bool IsDead() { return isdead; }
	std::vector<Component*> GetComponent() { return m_component; }
    Mesh& GetMesh();
    Transform& GetTransform();
	Object_Draw_Type GetObjectDrawType() { return m_draw_type; }
	
	void Set_HUD_Object_Size(const vector2 size) { HUD_Object_size = size; }
    void SetObjectType(ObjectType obj_type) { object_type = obj_type; }
    void SetObjectDead() { isDead = true; }

public:
    ObjectType GetObjectType() { return object_type; }
	std::vector<Component*> GetComponent() { return components; }
	vector2 Get_Object_HUD_Size() { return HUD_Object_size; }
    Mesh& GetMesh();
    Transform& GetTransform();

    template <typename COMPONENT>
    COMPONENT* GetComponentByTemplate() const;

private:
	bool isdead = false;
	Object_Draw_Type m_draw_type = Object_Draw_Type::None;
    Mesh m_mesh{};
    Transform m_transform{};
    std::vector<Component*> m_component;
	ObjectType object_type = ObjectType::None;
};

template <typename COMPONENT>
COMPONENT* Object::GetComponentByTemplate() const
{
    for (auto i : m_component)
    {
        if (typeid(COMPONENT) == typeid(*i))
        {
            return dynamic_cast<COMPONENT*>(i);
        }
    }
    return nullptr;
}
