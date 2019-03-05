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
#include "Physics.hpp"

Imgui_System IMGUI_;

bool Imgui_System::Initialize()
{
	//Imgui Setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	//ImGui::GetCurrentWindow()->WindowBorderSize

	const char* glsl_version = "#version 300 es";

	window = glfwGetCurrentContext();

	ImGui_ImplGlfw_InitForOpenGL(window, false);
	ImGui_ImplOpenGL3_Init(glsl_version);

	/*glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);
	glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
	glfwSetMouseButtonCallback(window, ImGui_ImplGlfw_MouseButtonCallback);
	glfwSetScrollCallback(window, ImGui_ImplGlfw_ScrollCallback);*/

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
	//Enemy Image List
	for (auto& p : std::filesystem::directory_iterator("asset/images/Enemies"))
	{
		enemyList.push_back(enemy_dir + p.path().filename().string());
	}
	//Sound list in project directory
	for (auto& p : std::filesystem::directory_iterator("asset/sounds"))
	{
		soundList.push_back(p.path().filename().string());
	}
	//Tile list in project directory
	for (auto& p : std::filesystem::directory_iterator("asset/images/Tiles/Non_Ani"))
	{
		non_ani_tileList.push_back(non_ani_tile_dir + p.path().filename().string());
	}
	for (auto& p : std::filesystem::directory_iterator("asset/images/Tiles/Ani"))
	{
		ani_tileList.push_back(ani_tile_dir + p.path().filename().string());
	}

	// Add texture into imgui
	for (auto& temp : non_ani_tileList)
	{
		auto texture = ImageHelper(temp);
		non_ani_tileList_buttons.insert(std::make_pair(temp, (void*)(intptr_t)texture));
	}
	for (auto& temp : ani_tileList)
	{
		auto texture = ImageHelper(temp);
		ani_tileList_buttons.insert(std::make_pair(temp, (void*)(intptr_t)texture));
	}

	for(auto& temp : enemyList)
	{
		auto texture = ImageHelper(temp);
		enemy_buttons.insert(std::make_pair(temp, (void*)(intptr_t)texture));
	}

	std::cout << "IMGUI Initialization Successful" << std::endl;

	return true;
}

void Imgui_System::Update(float dt)
{
	if (Input::IsKeyTriggered(GLFW_KEY_TAB))
	{
		show_window = !show_window;
		if (!show_window)
			imgui_key_call_back = false;
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
				{
					selectObj = obj->get();
					imgui_key_call_back = true;
				}
			}
		}

		if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			if (selectObj)
				selectObj->SetTranslation(Input::GetMousePos(1.f));
			//imgui_key_call_back = false;
		}

		if (is_normal_tile)
		{
			if (Input::IsKeyPressed(GLFW_KEY_G))
			{
				Tile_Map_.Make_Tile(tile_path, Tile_Type::Graphical);
			}
		}
		else
		{
			if (Input::IsKeyPressed(GLFW_KEY_G))
			{
				Tile_Map_.Make_Ani_Tile(tile_path, Tile_Type::Graphical);
			}
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

	//ImGui::ShowDemoWindow(&show_window);
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

	if (ImGui::RadioButton("Object Creator", object_creator))
	{
		object_creator = !object_creator;
		object_editor = false;
		tile_editor = false;
	}

	ImGui::SameLine();

	if (ImGui::RadioButton("Object Editor", object_editor))
	{
		object_editor = !object_editor;
		object_creator = false;
		tile_editor = false;
	}
	
	//ImGui::SameLine();

	//if (ImGui::RadioButton("Sound Editor", sound_editor))
	//	sound_editor = !sound_editor;

	ImGui::SameLine();

	if (ImGui::RadioButton("Tile Editor", tile_editor))
	{
		tile_editor = !tile_editor;
		object_creator = false;
		object_editor = false;
	}

	// Create editor window
	ObjectCreator(object_creator);
	ObjectEditor(object_editor);
	TileEditor(tile_editor);

	for (int i = 0; i < 50; i++)
	{
		if(tile_editor)
		{
			if (i == 5)
				break;
		}
		if(object_editor)
		{
			if (i == 30)
				break;
		}
		if (object_creator)
		{
			if (i == 30)
				break;
		}
		ImGui::Spacing();
	}

	if(ImGui::Button("Save Objects"))
	{
		for(auto& obj : Objectmanager_.GetObjectMap())
		{
			JSON_.ObjectsToDocument(obj.get());
		}
		JSON_.GetObjectDocument().SetObject();
	}

	ImGui::SameLine();

	if (ImGui::Button("Load Objects"))
	{
		JSON_.LoadObjectFromJson();
	}

	if(ImGui::Button("Save G_Tiles"))
	{
		for (auto& tiles : Tile_Map_.GetGraphicsTiles())
		{
			JSON_.TilesToDocument(tiles.first, tiles.second, Tile_Type::Graphical);
		}
		JSON_.GetTileDocument().SetObject();
	}

	ImGui::SameLine();

	if (ImGui::Button("Load G_Tiles"))
	{
		JSON_.LoadTilesFromJson(Tile_Type::Graphical);
	}

	/*if (ImGui::Button("Save P_Tiles"))
	{
		JSON_.SaveTilesToJson(Tile_Type::Physical);
	}
	ImGui::SameLine();

	if (ImGui::Button("Load P_Tiles"))
	{
		JSON_.LoadTilesFromJson(Tile_Type::Physical);
	}*/

	// Delete ALL Object
	if (ImGui::Button("Clear All"))
	{
		Objectmanager_.GetObjectMap().clear();
		Physics_.ResetPreviousSize();
	}

	ImGui::End();
}

void Imgui_System::ObjectCreator(bool object_creator)
{
	if (!object_creator)
		return;

	ImGui::Text("Enemy");
	ImGui::Separator();

	ImGui::Button("Slime");

	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}
	if (ImGui::IsItemDeactivated())
	{
		Object* obj = new Object;
		obj->SetScale({ 100.f,100.f });
		obj->SetTranslation({ Input::GetMousePos(Graphics::camera_zoom).x, Input::GetMousePos(Graphics::camera_zoom).y });
		obj->SetDepth(0);
		obj->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		obj->AddComponent(new Animation("asset/images/Enemies/slime.png", "slime", 6, 0.05f));

		Objectmanager_.AddObject(obj);
	}

	ImGui::SameLine();

	ImGui::Button("Scorpion");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* obj = new Object;
		obj->SetScale({ 100.f,100.f });
		obj->SetTranslation({ Input::GetMousePos(Graphics::camera_zoom).x, Input::GetMousePos(Graphics::camera_zoom).y });
		obj->SetDepth(0);
		obj->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		obj->AddComponent(new Animation("asset/images/Enemies/scol.png", "scol", 6, 0.05f));

		Objectmanager_.AddObject(obj);
	}

	ImGui::Text("Boss");
	ImGui::Separator();

	ImGui::Button("Boss");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* obj = new Object;
		obj->SetScale({ 100.f,100.f });
		obj->SetTranslation({ Input::GetMousePos(Graphics::camera_zoom).x, Input::GetMousePos(Graphics::camera_zoom).y });
		obj->SetDepth(0);
		obj->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		obj->AddComponent(new Animation("asset/images/Enemies/boss.png", "boss", 5, 0.05f));

		Objectmanager_.AddObject(obj);
	}
}

void Imgui_System::ObjectEditor(bool object_editor)
{
	if (!object_editor)
		return;

	if (selectObj == nullptr)
		return;

	selectObj->GetTransform().Imgui_Transform();

	if(selectObj->GetComponentByTemplate<Animation>() != nullptr)
		selectObj->GetComponentByTemplate<Animation>()->Imgui_Animation();

	SpriteHelper();

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


void Imgui_System::TileEditor(bool tile_editor)
{
	if (!tile_editor)
		return;

	int i = 1;
	int j = 1;

	ImGui::Text("Non-Animated Tiles");
	ImGui::Separator();

	for (auto& temp : non_ani_tileList_buttons)
	{
		if(ImGui::ImageButton(temp.second, ImVec2(16, 16)))
		{
			//non_ani_tile_selected = ImGui::IsItemClicked(Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT));
			tile_path = temp.first;
			is_normal_tile = true;
		}

		if (i != 8)
			ImGui::SameLine();
		else
			i = 0;
		i++;
	}

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Text("Animated Tiles");

	for (auto& temp : ani_tileList_buttons)
	{
		if (ImGui::ImageButton(temp.second, ImVec2(16, 16)))
		{
			//ani_tile_selected = ImGui::IsItemClicked(Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT));
			tile_path = temp.first;
			is_normal_tile = false;
		}

		if (j != 8)
			ImGui::SameLine();
		else
			j = 0;
		j++;
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

