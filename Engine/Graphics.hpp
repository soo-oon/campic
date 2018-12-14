/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Graphics.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#pragma once

#include "Shader.hpp"
#include "Transform.hpp"
#include "Object.hpp"
#include "Sprite.hpp"
#include "System.hpp"
#include <vector>
#include "Objectmanager.hpp"
#include "Camera.hpp"

class Animation;

enum class Type : int
{
	solid_obj,
	sprite,
	particle,
	count
};

class Graphics : public System
{
public:
	static float checking_zoom;

	Graphics() = default;
	~Graphics() = default;

	bool Initialize() override;
	void Update(float dt) override;
	void Draw(Objectmanager* objects);
	void HUD_Draw(Objectmanager* objects, Objectmanager* hud_obj);
	void EndDraw();
	void Quit() override;

	void SetNDC();
	void SetDisplaySize_G(vector2 size, State* state);
	static vector2 camera_center;

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
	struct particle
	{
		vector2 position;
		vector2 particleCoordinate;
	};

	affine2d CalculateModelToNDCTransform(const Transform& transform) const;

	void Draw(const Transform& transform, const std::vector<solidshape>& vertexes,
		PointListType draw_type, Color color);
	void Draw(const Transform& transform, const std::vector<collsionbox>& vertexes,
		PointListType draw_type, Color color);
	void Draw(const Transform& transform, const std::vector<texture>& vertexes,
		PointListType draw_type, Color color, Sprite* sprite);
	void Draw(const Transform& transform, const std::vector<animaition>& vertexes,
		PointListType draw_type, Color color, Sprite* sprite);
	void Draw(const Transform& transform, const std::vector<particle>& vertexes,
		PointListType draw_type, Color color, Sprite* sprite);

	void DescribSolidVertexPosition();
	void DescribVertexPosition();
	void DescribParticlePosition();

private:
	bool Iscamera = false;
	Camera* temp_camera = nullptr;
	

	static const int NumberOfVertexTypes = (int)Type::count;
	vector2 displaysize{};

	affine2d projection = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	unsigned int lastBoundTexture = 0;

	Shader Solidshader{};
	Shader Spriteshader{};
	Shader Particleshader{};
	//TODO make postprocessing and particle shader

	GLuint vertexAttributes[NumberOfVertexTypes] = { 0 };
	GLuint vertexBuffer[NumberOfVertexTypes] = { 0 };

	std::vector<solidshape> shapes{};
	std::vector<texture> sprite{};
	std::vector<animaition> animation{};
	std::vector<collsionbox> collsionboxes{};
	std::vector<particle> particles{};
};
