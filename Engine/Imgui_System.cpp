/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: imgui_System.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Kang Tae Wook
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Imgui_System.hpp"
#include <iostream>
#include "Graphics.hpp"
#include "stb_image.h"
#include <imgui_internal.h>
#include "Tile_Map.hpp"

Imgui_System IMGUI_;

bool Imgui_System::Initialize()
{
	//Imgui Setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	const char* glsl_version = "#version 300 es";

	window = glfwGetCurrentContext();

	ImGui_ImplGlfw_InitForOpenGL(window, false);
	ImGui_ImplOpenGL3_Init(glsl_version);

	glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);

	ImGui::StyleColorsDark();

	//Imgui configs
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.FontDefault = NULL;
	io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos; 
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	//Image list in project directory
	for (auto& p : std::filesystem::directory_iterator("asset/images"))
	{
		imageList.push_back(p.path().filename().string());
	}
	//Sound list in project directory
	for (auto& p : std::filesystem::directory_iterator("asset/sounds"))
	{
		soundList.push_back(p.path().filename().string());
	}
	//Tile list in project directory
	for (auto& p : std::filesystem::directory_iterator("asset/images/Tiles"))
	{
		tileList.push_back(tile_dir + p.path().filename().string());
	}

	for (auto& temp : tileList)
	{
		auto texture = ImageHelper(temp);
		tile_buttons.insert(std::make_pair(temp, (void*)(intptr_t)texture));
	}

	std::cout << "IMGUI Initialization Successful" << std::endl;

	return true;
}

void Imgui_System::Update(float dt)
{
	// Tile Draw Call

	if (Input::IsKeyTriggered(GLFW_KEY_TAB))
	{
		show_window = !show_window;
	}

	if (show_window)
	{
		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			for (auto obj = Objectmanager_.GetObjectMap().begin(); obj != Objectmanager_.GetObjectMap().end(); ++obj)
			{
				if (Input::GetMousePos(1.f).x < obj->get()->GetTransform().GetTranslation().x + obj->get()->GetTransform().GetScale().x &&
					Input::GetMousePos(1.f).x > obj->get()->GetTransform().GetTranslation().x - obj->get()->GetTransform().GetScale().x &&
					Input::GetMousePos(1.f).y < obj->get()->GetTransform().GetTranslation().y + obj->get()->GetTransform().GetScale().y &&
					Input::GetMousePos(1.f).y > obj->get()->GetTransform().GetTranslation().y - obj->get()->GetTransform().GetScale().y
					)
					selectObj = obj->get();
			}
		}

		if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			if (selectObj)
				selectObj->SetTranslation(Input::GetMousePos(1.f));
		}

		if (tile_selected == 0)
		{
			if (Input::IsKeyPressed(GLFW_KEY_G))
			{
				Tile_Map_.Make_Tile(tile_path, Tile_Kind::Graphics);
                                std::cout << Tile_Map_.GetGraphicsTiles().size() << std::endl;
			}
			tile_selected = 1;
		}
	}
}

void Imgui_System::Quit()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Imgui_System::Draw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
		
	Editor(show_window);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	window = glfwGetCurrentContext();
	glfwSwapBuffers(window);
}

void Imgui_System::Editor(bool show_window)
{
	if (!show_window)
		return;

	ImGui::SetNextWindowSize(ImVec2(400, 400));
	if (!ImGui::Begin("ImGui Editor", &show_window, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
		return;
	}

	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("Frame Rate (%.1f FPS)", io.Framerate);

	if (ImGui::RadioButton("Object Editor", object_editor))
		object_editor = !object_editor;
	
	//ImGui::SameLine();

	//if (ImGui::RadioButton("Sound Editor", sound_editor))
	//	sound_editor = !sound_editor;

	ImGui::SameLine();

	if (ImGui::RadioButton("Tile Editor", tile_editor))
		tile_editor = !tile_editor;

	// Create editor window
	ObjectEditor(object_editor);
	TileEditor(tile_editor);
	//SoundEditor(sound_editor);

	ImGui::End();
}

void Imgui_System::ObjectEditor(bool object_editor)
{
	if (!object_editor)
		return;

	if (selectObj == nullptr)
		return;

	selectObj->GetTransform().Imgui_Transform();

	SpriteHelper();
	//SoundHelper();

	//SoundHelper(sound_path);

	if (ImGui::Button("Delete"))
	{
		for (auto object = Objectmanager_.GetObjectMap().begin(); object != Objectmanager_.GetObjectMap().end();)
		{
			if(object->get() == selectObj)
			{
				object = Objectmanager_.GetObjectMap().erase(object);
				selectObj = nullptr;
			}
			else
			{
				object++;
			}
		}
	}

	// Delete ALL Object
	if (ImGui::Button("Clear All"))
	{
		Objectmanager_.GetObjectMap().clear();
	}
}

void Imgui_System::SpriteHelper()
{
	if (ImGui::TreeNode("Sprite"))
	{
		static std::string current_item = image_path;

		if (ImGui::BeginCombo("Select texture", current_item.c_str()))
		{
			for (int n = 0; n < imageList.size(); n++)
			{
				bool is_selected = (current_item.c_str() == imageList[n].c_str());
				if (ImGui::Selectable(imageList[n].c_str(), is_selected))
					current_item = imageList[n].c_str();
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		if (selectObj->GetComponentByTemplate<Sprite>() != nullptr)
		{
			if (ImGui::Button("Change Texture"))
			{
				selectObj->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/" + current_item);
			}
		}
		else
		{
			if (ImGui::Button("Add Texture"))
			{
				selectObj->AddComponent(new Sprite("asset/images/" + current_item));
			}
		}
		ImGui::TreePop();
	}
}

void Imgui_System::SoundHelper()
{
	if (ImGui::TreeNode("Sound"))
	{
		static std::string current_item = sound_path;

		if (ImGui::BeginCombo("Select sound", current_item.c_str()))
		{
			for (int n = 0; n < soundList.size(); n++)
			{
				bool is_selected = (current_item.c_str() == soundList[n].c_str());
				if (ImGui::Selectable(soundList[n].c_str(), is_selected))
					current_item = soundList[n].c_str();
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		if (selectObj->GetComponentByTemplate<Sound>() != nullptr)
		{
			if (ImGui::Button("Change Sound"))
				selectObj->GetComponentByTemplate<Sound>()->AddSound("asset/sounds/" + current_item);
			
			ImGui::SameLine();
			
			if (ImGui::Button("Play Sound"))
				selectObj->GetComponentByTemplate<Sound>()->Play("asset/sounds/" + current_item);
		}
		else
		{
			if (ImGui::Button("Add Sound"))
			{
				selectObj->AddComponent(new Sound("asset/sounds/" + current_item, AudioManager::CATEGORY_SFX, 4));
			}
		}
		ImGui::TreePop();
	}
}

void Imgui_System::SoundEditor(bool sound_editor)
{
	if (!sound_editor)
		return;

	static std::string current_sound = "";
	
	// The second parameter is the label previewed before opening the combo.
	if (ImGui::BeginCombo("Select Sound", current_sound.c_str())) 
	{
		for (int n = 0; n < soundList.size(); n++)
		{
			// You can store your selection however you want, outside or inside your objects
			bool is_selected = (current_sound.c_str() == soundList[n].c_str()); 
			if (ImGui::Selectable(soundList[n].c_str(), is_selected))
				current_sound = soundList[n].c_str();
				if (is_selected)
					ImGui::SetItemDefaultFocus();   
		}
		ImGui::EndCombo();
	}

	const std::string current_path = "asset/sounds/";

	if (ImGui::Button("Load SFX"))
	{
		AudioManager_.LoadSFX(current_path + current_sound);
	}
	ImGui::SameLine();
	if (ImGui::Button("Load Song"))
	{
		AudioManager_.LoadSong(current_path + current_sound);
	}

	if (ImGui::Button("Play SFX"))
	{
		//AudioManager_.PlaySFX(current_path + current_sound,4,4,4,4);
	}
	ImGui::SameLine();
	if (ImGui::Button("Play Song"))
	{
		AudioManager_.PlaySong(current_path + current_sound);
	}

	if(ImGui::Button("Stop SFXs"))
	{
		AudioManager_.StopSFXs();
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop Songs"))
	{
		AudioManager_.StopSongs();
	}
}

void Imgui_System::TileEditor(bool tile_editor)
{
	if (!tile_editor)
		return;

	tile_selected = ImGui::GetActiveID();
	int i = 1;

	for (auto& temp : tile_buttons)
	{
		//auto texture = TileHelper(temp);
		if(ImGui::ImageButton(temp.second, ImVec2(16, 16)))
		{
			tile_selected = ImGui::IsItemClicked(Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT));
			tile_path = temp.first;
		}

		if (i != 8)
			ImGui::SameLine();
		else
			i = 0;
		i++;
	}
}

GLuint Imgui_System::ImageHelper(std::string path)
{
	std::vector<GLuint> texture_data;

	int my_image_width, my_image_height;
	unsigned char* my_image_data = stbi_load(path.c_str(),
		&my_image_width, &my_image_height, nullptr, STBI_rgb_alpha);

	// Turn the RGBA pixel data into an OpenGL texture:
	GLuint my_opengl_texture;
	glGenTextures(1, &my_opengl_texture);
	glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, my_image_width, my_image_height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, my_image_data);

	return my_opengl_texture;
}


// Creating Object
//ImGui::Button("Create Object");

//Object obj;

/*if (ImGui::IsItemActive())
{
	ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
}

if (ImGui::IsItemDeactivated())
{
	obj.SetScale({ 100.f,100.f });
	obj.SetTranslation({ Input::GetMousePos(Graphics::camera_zoom).x, Input::GetMousePos(Graphics::camera_zoom).y });
	obj.SetDepth(0);
	obj.SetMesh(mesh::CreateBox(1, { 255, 0, 0, 255 }));

	obj.AddComponent(new Sprite());
	obj.GetComponentByTemplate<Sprite>()->ChangeSprite(image_dir + image_path);
}

Objectmanager_.AddObject(obj);*/

