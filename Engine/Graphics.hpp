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
#include <vector>
#include "Font.hpp"
#include "Particle_Generator.hpp"

class Sprite;
class ObjectManager;

enum class GraphicsType : int
{
	solid_obj,
	sprite,
	particle,
	font,
	count
};

class Graphics
{
public:
	bool Initialize();
	void Update(float dt);
	void Quit();

	void BeginDraw();
	void Draw();
	void HUD_Draw();
    void Tile_Draw();
	void EndDraw();

	void SetNDC();

	vector2 GetDisplaySize() { return displaysize; }

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
	struct font
	{
		vector2 position;
		vector2 fontCoordinate;
	};


	affine2d CalculateModelToNDCTransform(const Transform& transform) const;

	//void DrawParticle(Object* obj);

	void DrawSolidShape(Object* obj);

	void DrawSprite(Object* obj, Sprite* sprite_);

	void DrawCollisionBox(Object* obj, Collision* collision);

	void DrawAnimation(Object* obj, Animation* animation_);

	void DrawParticle(Particle_Generator* particles);

	void DrawFont(Object* obj, Font* font);

	/*
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

	void Draw(const Transform& transform, const std::vector<font>& vertexes,
		PointListType draw_type, Color color, Font* font, int index);
	*/

	void DescribSolidVertexPosition();
	void DescribVertexPosition();
	void DescribParticlePosition();
	void DescribFontPosition();

private:
	bool Iscamera = false;
	Camera* temp_camera = nullptr;

	static const int NumberOfVertexTypes = (int)GraphicsType::count;
	vector2 displaysize{};

	affine2d projection = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	unsigned int lastBoundTexture = 0;

	Shader Solidshader{};
	Shader Spriteshader{};
	Shader Particleshader{};
	Shader Fontshader{};

	unsigned vertexAttributes[NumberOfVertexTypes] = { 0 };
	unsigned vertexBuffer[NumberOfVertexTypes] = { 0 };

	std::vector<solidshape> shapes{};
	std::vector<texture> sprite{};
	std::vector<animaition> animation{};
	std::vector<collsionbox> collsionboxes{};
	std::vector<particle> particles{};
	std::vector<font> fontes{};
};

extern Graphics Graphics_;