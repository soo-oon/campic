#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <string>
#include <unordered_map>
#include FT_FREETYPE_H

#include "Component.hpp"
#include "vector2.hpp"
#include "Mesh.hpp"

struct Character
{
	GLuint textureID;
	vector2 size;
	vector2 bearing;
	GLuint advance;
};

class Font : public Component
{
public:
	Font(std::string text_ = "Empty", std::string path_ = "asset/font/default.ttf", Color color = {0,0,0,255})
	: text(text_), path(path_), m_color(color)
	{}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	void SetText(std::string text_);
	void SetPath(std::string path_);

	void BindTexture(int index);
	std::vector<Mesh>& GetFontMeshes() { return font_mesh; }

	std::string GetText() { return text; }
	std::string GetPath() { return path; }
	Color GetFontColor() { return m_color; }

private:
	void MakeFontMesh();
	void LoadFontData();
	std::vector<Mesh> font_mesh;
	std::unordered_map<GLchar, Character> characters;

	std::string text;
	std::string path;
	Color m_color;
};