#pragma once
#include "Application.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "System.hpp"
#include "Objectmanager.hpp"
#include "Animation.hpp"
#include "Collision.hpp"
#include "Sound.hpp"
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

class Imgui_System: public System
{
public:
	~Imgui_System()
	{
	};

	bool Initialize() override;
	void Update(float dt) override;
	void Quit() override;

	void Draw();
	void ObjectManger(bool show_window);
	void Sound_Option(bool show_window);
	void componentHelper(Object* object, ComponentType);

	void SetObjectManger(Objectmanager* obj_manager) { object_manager = obj_manager; }
	void SetSoundManager(Sound* _sound_manager) { sound_manager = _sound_manager; };

	static std::vector<std::string> soundlist;

	void Editor(bool show_editor);

private:
	GLFWwindow* window = nullptr;
	Objectmanager* object_manager = nullptr;
	
	bool show_window = true;
	bool show_mapeditor_window = false;
	bool show_editor = false;

	std::vector<std::string> imagelist;
	std::string new_object = "object0";

	Sound* sound_manager = nullptr;

	//now these functions are mine
	void AllObjectTree(std::vector<std::string> obj_list);
	void SpriteObject(Object* sprite_obj);
	void NonSpriteObject(Object* sprite_obj);
	//for creating object
	size_t object_count = -1;
	std::string object_name = "object";
	Object* newObject = nullptr;
};
