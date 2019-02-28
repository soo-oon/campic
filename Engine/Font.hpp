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
	Font(std::string text_, std::string path_) 
	: text(text_), path(path_)
	{}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;
	void LoadFontData();

	void BindTexture(int index);
	std::vector<Mesh>& GetFontMeshes() { return font_mesh; }

	std::string GetText() { return text; }
	std::string GetPath() { return path; }

private:
	std::vector<Mesh> font_mesh;
	//Mesh mesh;
	std::unordered_map<GLchar, Character> characters;

	//FT_Library ft;
	//FT_Face face;

	std::string text;
	std::string path;
};