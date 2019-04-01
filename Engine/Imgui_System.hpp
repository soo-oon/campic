/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: imgui_System.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Kang Tae Wook
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "Application.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Objectmanager.hpp"
#include "Animation.hpp"
#include "Collision.hpp"
#include "AudioManager.hpp"
#include <filesystem>
#include <string>
#include <unordered_map>

class Imgui_System
{
public:
	bool Initialize();
	void Update(float dt);
	void Quit();

	void Draw();
	void Editor(bool show_window);
	void ObjectCreator(bool object_creator);
	void ObjectEditor(bool object_editor);

	void TileEditor(bool tile_editor);
	GLuint ImageHelper(std::string path);

	// Helper
	void SpriteHelper();

private:
	GLFWwindow* window = nullptr;
	
	bool show_window = false;
	bool object_creator = false;
	bool object_editor = false;
	bool sound_editor = false;
	bool tile_editor = false;

	std::vector<std::string> imageList;
	std::vector<std::string> enemyList;
	std::vector<std::string> soundList;
	std::vector<std::string> ani_tileList;
	std::vector<std::string> non_ani_tileList;

	std::unordered_map<std::string,ImTextureID> ani_tileList_buttons;
	std::unordered_map<std::string, ImTextureID> non_ani_tileList_buttons;
	std::unordered_map<std::string, ImTextureID> enemy_buttons;

	std::string image_path;
	std::string sound_path;
	std::string tile_path;

	std::string image_dir = "asset/images/";
	std::string enemy_dir = "asset/images/Enemies/";
	std::string sound_dir = "asset/sounds/";
	std::string ani_tile_dir = "asset/images/Tiles/Ani/";
	std::string non_ani_tile_dir = "asset/images/Tiles/Non_Ani/";

	ImGuiID ani_tile_selected = false;
	ImGuiID non_ani_tile_selected = false;

	bool is_normal_tile = true;
	bool graphics_tile = false;

	Object* selectObj = nullptr;
	Object* player_ = nullptr;
};

extern Imgui_System IMGUI_;