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
	void SetTranslation(const vector2& position);
	void SetScale(const vector2& scale);
	void SetRotation(float& rotation);
	void SetDepth(float& depth);

	Mesh& GetMesh();
	Transform& GetTransform();

private:
	Mesh mesh{};
	Transform transform{};
	std::vector<Component*> components;
};
