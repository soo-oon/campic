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
    Background,
    Projectile,
	Font,
	Capture_Obj,
	Tile,
	Button,
	Polaroid,
    None,
}; 

class Object
{
public:
	Object()
	{}

	Object(const Object& obj);

    void AddComponent(Component* component);
    void AddInitComponent(Component* component);


public:
    void SetMesh(Mesh mesh);
    void SetTranslation(const vector2& position);
    void SetScale(const vector2& scale);
    void SetRotation(const float& rotation);
    void SetDepth(const float& depth);
	void SetParent(const Transform* transform_);
	void SetIsDead(bool condition);

	bool Isvisible();
	void SetVisible();
	void SetInvisible();

public:
	bool IsDead() { return isdead; }
	std::vector<Component*> GetComponent() { return m_component; }
    Mesh& GetMesh();
    Transform& GetTransform();
	ObjectType GetObjectType() {return object_type;}
    void SetObjectType(ObjectType obj_type) { object_type = obj_type; }
    void SetObjectDead() { isdead = true; }

    template <typename COMPONENT>
    COMPONENT* GetComponentByTemplate() const;

private:
	bool isdead = false;
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
