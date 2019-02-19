#pragma once
#include "Component.hpp"
#include "BitmapFont.hpp"
#include <string>
#include "Mesh.hpp"

class Font : public Component
{
public:
	Font(std::string text_, std::string font_path_, Color color_ = {255,255,255})
		: text(text_), font_path(font_path_), color(color_)
	{
		font.LoadFromFile(font_path);
	}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	//std::string GetString() const;
	void SetString(const std::string text_string) { text = text_string; }
	const BitmapFont GetFont() const { return font; }
	void SetFont(std::string font_path_);
	Color GetFillColor() const { return color; }
	void SetFillColor(Color fill_color);

        //const Sprite* sprite = nullptr;
	std::unordered_map<int, Mesh> GetFontMesh() { return meshes; }

private:
	void BuildNewMeshesIfNeeded() const;

private:
	std::string text;
	std::string font_path;
	BitmapFont font; 
	Color color{ 255, 255, 255, 255 };
	mutable bool needNewMeshes = false;
	mutable std::unordered_map<int, Mesh> meshes{};
};
