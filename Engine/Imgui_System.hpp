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
	~Imgui_System()
	{
	};

	bool Initialize();
	void Update(float dt);
	void Quit();

	void Draw();
	void Editor(bool show_editor);
	//void Sound_Option(bool show_window);
	//void componentHelper(Object* object, ComponentType);
	//void ObjectAnimation(Object* obj);
	//void ObjectCharacter(Object * obj);

	//void SetObjectManger(Objectmanager* obj_manager) { object_manager = obj_manager; }
	//void SetSoundManager(Sound* _sound_manager) { sound_manager = _sound_manager; };

private:
	GLFWwindow* window = nullptr;
	Objectmanager* object_manager = nullptr;
	
	bool show_window = false;

	std::vector<std::string> imageList;
	std::vector<std::string> soundList;
	//std::string new_object = "object0";

	//Sound* sound_manager = nullptr;

	//void AllObjectTree(std::vector<std::string> obj_list);
	//void ObjectSprite(Object* sprite_obj);
	//for creating object
	//size_t object_count = -1;
	//std::string object_name = "object";
	//Object* newObject = nullptr;
};

extern Imgui_System IMGUI_;