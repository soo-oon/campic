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

class Object
{
public:
    void AddComponent(Component* component);
    void Add_Init_Component(Component* component);
    void SetMesh(Mesh mesh);
    void SetTranslation(const vector2& position);
    void SetScale(const vector2& scale);
    void SetRotation(const float& rotation);
    void SetDepth(const float& depth);
	void SetParent(const Transform* transform_);
    void SetGravity(float gravity_own);
	void Set_HUD_Object_Size(const vector2 size) { HUD_Object_size = size; }

	std::vector<Component*> GetComponent() { return components; }
	vector2 Get_Object_HUD_Size() { return HUD_Object_size; }

    float GetGravity();

    Mesh& GetMesh();
    Transform& GetTransform();

    template <typename COMPONENT>
    COMPONENT* GetComponentByTemplate() const;

	std::string texture_path = "no_texture";
	int object_id = 0;
	int component_type_id = 0;

private:
	float gravity = 1;
    Mesh object_mesh{};
    Transform transform{};
	vector2 HUD_Object_size{};
    std::vector<Component*> components;
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
