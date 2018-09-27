#pragma once

#include "System.hpp"
#include "Mesh.hpp"
#include "Transform.hpp"
#include <glm/vec3.hpp>
#include <vector>

enum class ShaderTypes : int
{
	SolidColor,
	InterpolatedColor,
	TextureWithSolidColor,
	Count
};

struct RenderStates
{
	ShaderTypes shaderType = ShaderTypes::SolidColor;
	Transform transform{};
};

class Graphics : public System
{
public:
	bool Initialize() override;
	void Update(float dt) override;
	void Quit() override;
};