#pragma once

#include "Shader.hpp"
#include "Transform.hpp"
#include "Object.hpp"
#include "Sprite.hpp"
#include "System.hpp"
#include <vector>

enum class Type : int
{
	soild,
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
	void Draw(Object& object);
	void EndDraw();
	void Quit() override;

	void SetNDC();
	void SetDisplaySize_G(vector2 size) { displaysize = size; }

private:
	struct Texture
	{
		vector2 position;
		vector2 textureCoordinate;
	};

	void Draw(const Transform& transform, const std::vector<Texture>& vertexes, 
		PointListType draw_type, const Color color, Sprite* sprite);
	void DescribVertexPosition();

private:
	static const int NumberOfVertexTypes = (int)Type::count;
	vector2 displaysize{};

	affine2d projection = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	unsigned int lastBoundTexture = 0;

	Shader shader{};
	GLuint vertexAttributes[NumberOfVertexTypes] = { 0 };
	GLuint vertexBuffer[NumberOfVertexTypes] = { 0 };
	std::vector<Texture> sprite{};
};