#pragma once
#include <vector>
#include "Component.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include <typeinfo>

class Object
{
public:
    void AddComponent(Component* component);
    void SetMesh(Mesh mesh_);
    void SetTranslation(const vector2& position);
    void SetScale(const vector2& scale);
    void SetRotation(const float& rotation);
    void SetDepth(const float& depth);
    void SetGravity(float gravity_own);
    float GetGravity();

    Mesh& GetMesh();
    Transform& GetTransform();
    template <typename COMPONENT>
    COMPONENT* GetComponentByTemplate() const;

private:
	float gravity = 1;
    Mesh mesh{};
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
