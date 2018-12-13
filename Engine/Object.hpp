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

class Object
{
public:
	Object() = default;
	Object(const Object& rhs);


    void AddComponent(Component* component);
    void SetMesh(Mesh mesh);
    void SetTranslation(const vector2& position);
    void SetScale(const vector2& scale);
    void SetRotation(const float& rotation);
    void SetDepth(const float& depth);
    void SetGravity(float gravity_own);

	std::vector<Component*> GetComponent() { return components; }

    float GetGravity();

    Mesh& GetMesh();
    Transform& GetTransform();

    template <typename COMPONENT>
    COMPONENT* GetComponentByTemplate() const;

	std::string texture_path = "no_texture";
	int object_id = 0;
private:
	float gravity = 1;
    Mesh object_mesh{};
    Transform transform{};
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
