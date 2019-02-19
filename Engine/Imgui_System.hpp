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
Secondary : Ji Hun Park
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

enum class ComponentType
{
	Animation,
	Sprite,
	Character,
	RigidBody,
	Collision
};

class Imgui_System
{
public:
	bool Initialize();
	void Update(float dt);
	void Quit();

	void Draw();
	void Editor(bool show_window);
	void ObjectEditor(bool object_editor);
	void SoundEditor(bool sound_editor);

	void TileEditor(bool tile_editor);
	GLuint TileHelper(std::string path);

	// Helper
	void SpriteHelper();
	void SoundHelper();

private:
	GLFWwindow* window = nullptr;
	
	bool show_window = false;
	bool object_editor = false;
	bool sound_editor = false;
	bool tile_editor = false;

	std::vector<std::string> imageList;
	std::vector<std::string> soundList;
	std::vector<std::string> tileList;

	std::unordered_map<std::string,ImTextureID> tile_buttons;

	std::string image_path;
	std::string sound_path;
	std::string tile_path;

	std::string image_dir = "asset/images/";
	std::string sound_dir = "asset/sounds/";
	std::string tile_dir = "asset/images/Tiles/";

	//void AllObjectTree(std::vector<std::string> obj_list);
	//void ObjectSprite(Object* sprite_obj);

	std::vector<Object*> tiles;

	Object* selectObj = nullptr;
};

extern Imgui_System IMGUI_;