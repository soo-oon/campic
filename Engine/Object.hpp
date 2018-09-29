#pragma once
#include <vector>
#include "Component.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"

class Object
{
public:
	void AddComponent(Component* component);
	Component* GetComponent(unsigned ID);
	void SetMesh(Mesh mesh_);
	void SetTransform(Transform transform_);
	Mesh& GetMesh();
	Transform& GetTransform();

private:
	Mesh mesh{};
	Transform transform{};
	std::vector<Component*> components;
};
