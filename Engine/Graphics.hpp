#pragma once

#include "Shader.hpp"
#include "Transform.hpp"
#include "Object.hpp"
#include "Sprite.hpp"
#include "System.hpp"
#include <vector>
#include "Objectmanager.hpp"

class Animation;

enum class Type : int
{
	solid_obj,
	sprite,
	count
};

class Graphics : public System
{
public:
	Graphics() = default;
	~Graphics() = default;

	bool Initialize() override;
	void Update(float dt) override;
	void Draw(Objectmanager* objects);
	void EndDraw();
	void Quit() override;

	void SetNDC();
	void SetDisplaySize_G(vector2 size);

private:
	struct solidshape
	{
		vector2 position;
	};
	struct texture
	{
		vector2 position;
		vector2 textureCoordinate;
	};
	struct animaition
	{
		vector2 position;
		vector2 animationCoordinate;
	};
	struct collsionbox
	{
		vector2 position;
	};

	void Draw(const Transform& transform, const std::vector<solidshape>& vertexes,
		PointListType draw_type, Color color);
	void Draw(const Transform& transform, const std::vector<collsionbox>& vertexes,
		PointListType draw_type, Color color);
	void Draw(const Transform& transform, const std::vector<texture>& vertexes,
		PointListType draw_type, Color color, Sprite* sprite);
	void Draw(const Transform& transform, const std::vector<animaition>& vertexes,
		PointListType draw_type, Color color, Sprite* sprite);

	void DescribSolidVertexPosition();
	void DescribVertexPosition();

private:
	static const int NumberOfVertexTypes = (int)Type::count;
	vector2 displaysize{};

	affine2d projection = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	unsigned int lastBoundTexture = 0;

	Shader Solidshader{};
	Shader Spriteshader{};
	GLuint vertexAttributes[NumberOfVertexTypes] = { 0 };
	GLuint vertexBuffer[NumberOfVertexTypes] = { 0 };

	std::vector<solidshape> shapes{};
	std::vector<texture> sprite{};
	std::vector<animaition> animation{};
	std::vector<collsionbox> collsionboxes{};
};
