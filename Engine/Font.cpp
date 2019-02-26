#include <iostream>
#include "Font.hpp"
#include "Object.hpp"

bool Font::Initialize(Object * Ob)
{
	if (object == nullptr)
	{
		object = Ob;
	}
	LoadFontData();
	return true;
}

void Font::Update(float dt)
{
	/*auto obj_position = object->GetTransform().GetTranslation();

	for (auto c : text)
	{
		Mesh temp;

		Character ch = characters[c];

		GLfloat xpos = obj_position.x + ch.bearing.x * 1;
		GLfloat ypos = obj_position.y - (ch.size.y - ch.bearing.y) * 1;

		GLfloat w = ch.size.x * 1;
		GLfloat h = ch.size.y * 1;

		temp.AddPoint({ xpos, ypos });
		temp.AddTextureCoordinate({ 0, 1 });

		temp.AddPoint({ xpos + w, ypos });
		temp.AddTextureCoordinate({ 1, 1 });

		temp.AddPoint({ xpos, ypos + h });
		temp.AddTextureCoordinate({ 0,0 });

		temp.AddPoint({ xpos + w, ypos + h });
		temp.AddTextureCoordinate({ 1, 0 });

		temp.SetPointListType(PointListType::TriangleStrip);

		font_mesh.push_back(temp);

		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		obj_position.x += (ch.advance >> 6) * 1;
	}*/
}

void Font::Delete()
{
}

void Font::LoadFontData()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, path.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; ++c)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		Character character = {
			texture, vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			vector2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x };
		characters.insert(std::make_pair(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	auto obj_position = object->GetTransform().GetTranslation();

	for (auto c : text)
	{
		Mesh temp;

		Character ch = characters[c];

		GLfloat xpos = obj_position.x + ch.bearing.x * 1;
		GLfloat ypos = obj_position.y - (ch.size.y - ch.bearing.y) * 1;

		GLfloat w = ch.size.x * 1;
		GLfloat h = ch.size.y * 1;

		temp.AddPoint({ xpos, ypos });
		temp.AddTextureCoordinate({ 0, 1 });

		temp.AddPoint({ xpos + w, ypos });
		temp.AddTextureCoordinate({ 1, 1 });

		temp.AddPoint({ xpos, ypos + h });
		temp.AddTextureCoordinate({ 0,0 });

		temp.AddPoint({ xpos + w, ypos + h });
		temp.AddTextureCoordinate({ 1, 0 });

		temp.SetPointListType(PointListType::TriangleStrip);

		temp.AddColor({ 0,0,0,255 });

		font_mesh.push_back(temp);

		obj_position.x += (ch.advance >> 6) * 1;
	}
}

void Font::BindTexture(int index)
{
	glActiveTexture(GL_TEXTURE0);
	auto temp = characters[text.at(index)];
	glBindTexture(GL_TEXTURE_2D, temp.textureID);
}
