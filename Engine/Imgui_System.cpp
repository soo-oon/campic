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
#include "Capture.hpp"
#include "MovingObject.hpp"
#include "Projectile.hpp"
#include "UI.hpp"
//#include "Objectmanager.hpp"

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

	//glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
	//glfwSetMouseButtonCallback(window, ImGui_ImplGlfw_MouseButtonCallback);
	//glfwSetScrollCallback(window, ImGui_ImplGlfw_ScrollCallback);

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

	for (auto& temp : enemyList)
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
	}

	if (show_window)
	{
		glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);

		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			selectObj = Input::ClickObject();
		}

		if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			if (selectObj)
				selectObj->SetTranslation(Input::GetMousePos());
		}

		if (Input::IsKeyPressed(GLFW_KEY_I))
			Tile_Map_.Delete_Tile();

		if (is_normal_tile)
		{
			if (Input::IsKeyPressed(GLFW_KEY_G))
			{
				if (graphics_tile)
					Tile_Map_.Make_Tile(tile_path, Tile_Type::Graphical);
				else
					Tile_Map_.Make_Tile(tile_path, Tile_Type::Physical);
			}
		}
		else
		{
			if (Input::IsKeyPressed(GLFW_KEY_G))
			{
				if (graphics_tile)
					Tile_Map_.Make_Ani_Tile(tile_path, Tile_Type::Graphical);
				else
					Tile_Map_.Make_Ani_Tile(tile_path, Tile_Type::Physical);
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
		if (tile_editor)
		{
			if (i == 5)
				break;
		}
		if (object_editor)
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

	if (ImGui::Button("Save Level"))
	{
		StateManager_.GetCurrentState()->SaveLevel();
	}

	ImGui::SameLine();

	// Delete ALL Object
	if (ImGui::Button("Clear All"))
	{
		StateManager_.GetCurrentState()->UnLoad();
		Tile_Map_.GetGraphicsTiles().clear();
		Tile_Map_.GetPhysicalTiles().clear();
		Physics_.ResetPreviousSize();
	}

	ImGui::End();
}

void Imgui_System::ObjectCreator(bool object_creator)
{
	if (!object_creator)
		return;

	ImGui::Text("Archetype");
	ImGui::Separator();

	ImGui::Button("Player");

	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}
	if (ImGui::IsItemDeactivated())
	{
		Object* player = new Object();
		player->SetTranslation(Input::GetMousePos());
		player->SetScale({ 50.0f, 50.0f });
		player->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
		player->SetDepth(-0.5f);
		player->SetObjectType(ObjectType::Player);
		player->AddInitComponent(new RigidBody());
		player->AddInitComponent(new Collision(box_));
		player->AddInitComponent(new Sprite("asset/images/Player_Static.png"));
		//player->AddInitComponent(new Animation("asset/images/Player_Animation.png", "player", 5, 0.2f, true));
		Objectmanager_.AddObject(player);

		Objectmanager_.SetPlayer(player);
	}

	ImGui::SameLine();

	ImGui::Button("Capture Camera");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* player_camera = new Object();
		player_camera->SetScale({ 300.0f, 175.0f });
		player_camera->SetDepth(-0.2f);
		player_camera->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
		player_camera->SetObjectType(ObjectType::None);
		player_camera->AddInitComponent(new Animation("asset/images/camera_frame.png", "basic_camera", 2, 0.5, true));
		player_camera->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/cheese.png", "cheese", 2, 0.5, true);
		player_camera->AddInitComponent(new Capture(StateManager_.GetCurrentState()->GetStartPosition()));

		Objectmanager_.AddObject(player_camera);
		Objectmanager_.SetCaptureObject(player_camera);
	}

	ImGui::Text("Type target Level");
	static char buffer[100] = "";
	ImGui::InputText("", buffer, IM_ARRAYSIZE(buffer));

	ImGui::Button("Door");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* door = new Object();
		door->SetTranslation(Input::GetMousePos());
		door->SetScale({ 100, 100 });
		door->SetDepth(-0.5f);
		door->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
		door->SetObjectType(ObjectType::Door);
		door->AddComponent(new Sprite("asset/images/door.png"));
		door->AddComponent(new UI(buffer));

		Objectmanager_.AddObject(door);
	}

	ImGui::Separator();
	ImGui::Text("Archetype");

	ImGui::Button("Cannon");

	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* cannon = new Object();
		cannon->SetTranslation(Input::GetMousePos());
		cannon->SetScale({ 150,150 });
		cannon->SetObjectType(ObjectType::Item_Static);
		cannon->SetMesh(mesh::CreateBox());
		cannon->AddComponent(new Collision(box_));
		cannon->AddComponent(new Animation("asset/images/cannon.png", "cannon_standing", 5, 0.4f, true));
		cannon->GetComponentByTemplate<Animation>()->AddAnimaition("asset/images/cannon_fire.png", "cannon_fire", 6, 0.1f, false);
		cannon->AddComponent(new Projectile(4.0f, 10.0f, Projectile_Type::Cannon));
		cannon->GetComponentByTemplate<Projectile>()->SetFireDir({ 350, 0 });

		Objectmanager_.AddObject(cannon);
	}
	ImGui::SameLine();

	ImGui::Button("Weapon");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* weapon = new Object();
		weapon->SetTranslation(Input::GetMousePos());
		weapon->SetScale({ 100, 50 });
		weapon->SetObjectType(ObjectType::Item_Dynamic);
		weapon->SetMesh(mesh::CreateBox());
		weapon->AddComponent(new Sprite("asset/images/weapon.png"));
		weapon->AddComponent(new Collision(box_));
		weapon->AddComponent(new Projectile(1.0f, 3.0f, Projectile_Type::Weapon));
		weapon->GetComponentByTemplate<Projectile>()->SetFireDir({ 1000, 0 });

		Objectmanager_.AddObject(weapon);
	}

	ImGui::Separator();
	ImGui::Text("Moving Platform");

	ImGui::Button("Round-Down");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* RoundObject = new Object();
		RoundObject->SetScale({ 125.0f, 50.0f });
		RoundObject->SetTranslation(Input::GetMousePos());
		RoundObject->AddInitComponent(new RigidBody());
		RoundObject->GetComponentByTemplate<RigidBody>()->SetGravity(0);
		RoundObject->AddComponent(new MovingObject(5.0f, RoundObject->GetTransform().GetTranslation(), 100.0f, Direction::DOWN, MovementType::ROUND, 0.0f));
		RoundObject->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		RoundObject->AddInitComponent(new Collision());
		RoundObject->AddInitComponent(new Sprite("asset/images/UI/StartButton.png"));

		Objectmanager_.AddObject(RoundObject);
	}

	ImGui::SameLine();

	ImGui::Button("Round-Up");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* RoundObject = new Object();
		RoundObject->SetScale({ 125.0f, 50.0f });
		RoundObject->SetTranslation(Input::GetMousePos());
		RoundObject->AddInitComponent(new RigidBody());
		RoundObject->GetComponentByTemplate<RigidBody>()->SetGravity(0);
		RoundObject->AddComponent(new MovingObject(8.0f, RoundObject->GetTransform().GetTranslation(), 100.0f, Direction::UP, MovementType::ROUND, 0.0f));
		RoundObject->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		RoundObject->AddInitComponent(new Collision());
		RoundObject->AddInitComponent(new Sprite("asset/images/UI/StartButton.png"));

		Objectmanager_.AddObject(RoundObject);
	}

	ImGui::SameLine();

	ImGui::Button("Round-Left");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* RoundObject = new Object();
		RoundObject->SetScale({ 125.0f, 50.0f });
		RoundObject->SetTranslation(Input::GetMousePos());
		RoundObject->AddInitComponent(new RigidBody());
		RoundObject->GetComponentByTemplate<RigidBody>()->SetGravity(0);
		RoundObject->AddComponent(new MovingObject(2.0f, RoundObject->GetTransform().GetTranslation(), 100.0f, Direction::LEFT, MovementType::ROUND, 0.0f));
		RoundObject->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		RoundObject->AddInitComponent(new Collision());
		RoundObject->AddInitComponent(new Sprite("asset/images/UI/StartButton.png"));

		Objectmanager_.AddObject(RoundObject);
	}
	ImGui::SameLine();
	ImGui::Button("Round-Right");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* RoundObject = new Object();
		RoundObject->SetScale({ -125.0f, 50.0f });
		RoundObject->SetTranslation(Input::GetMousePos());
		RoundObject->AddInitComponent(new RigidBody());
		RoundObject->GetComponentByTemplate<RigidBody>()->SetGravity(0);
		RoundObject->AddComponent(new MovingObject(2.0f, RoundObject->GetTransform().GetTranslation(), 100.0f, Direction::RIGHT, MovementType::ROUND, 0.0f));
		RoundObject->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		RoundObject->AddInitComponent(new Collision());
		RoundObject->AddInitComponent(new Sprite("asset/images/UI/StartButton.png"));

		Objectmanager_.AddObject(RoundObject);
	}

	ImGui::Button("OneWay-Down");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* OneWayObject = new Object();
		OneWayObject->SetScale({ 50.0f, 50.0f });
		OneWayObject->SetTranslation(Input::GetMousePos());
		OneWayObject->AddInitComponent(new RigidBody());
		OneWayObject->GetComponentByTemplate<RigidBody>()->SetGravity(0);
		OneWayObject->AddComponent(new MovingObject(7.0f, OneWayObject->GetTransform().GetTranslation(), 100.0f, Direction::DOWN, MovementType::ONEWAY, 5.0f));
		OneWayObject->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		OneWayObject->AddInitComponent(new Collision());
		OneWayObject->AddInitComponent(new Sprite("asset/images/cannon_bullet.png"));

		Objectmanager_.AddObject(OneWayObject);
	}
	ImGui::SameLine();
	ImGui::Button("OneWay-Up");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* OneWayObject = new Object();
		OneWayObject->SetScale({ 50.0f, 50.0f });
		OneWayObject->SetTranslation(Input::GetMousePos());
		OneWayObject->AddInitComponent(new RigidBody());
		OneWayObject->GetComponentByTemplate<RigidBody>()->SetGravity(0);
		OneWayObject->AddComponent(new MovingObject(2.0f, OneWayObject->GetTransform().GetTranslation(), 100.0f, Direction::UP, MovementType::ONEWAY, 0.0f));
		OneWayObject->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		OneWayObject->AddInitComponent(new Collision());
		OneWayObject->AddInitComponent(new Sprite("asset/images/cannon_bullet.png"));

		Objectmanager_.AddObject(OneWayObject);
	}
	ImGui::SameLine();
	ImGui::Button("OneWay-Left");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* OneWayObject = new Object();
		OneWayObject->SetScale({ 50.0f, 50.0f });
		OneWayObject->SetTranslation(Input::GetMousePos());
		OneWayObject->AddInitComponent(new RigidBody());
		OneWayObject->GetComponentByTemplate<RigidBody>()->SetGravity(0);
		OneWayObject->AddComponent(new MovingObject(1.0f, OneWayObject->GetTransform().GetTranslation(), 100.0f, Direction::LEFT, MovementType::ONEWAY, 3.0f));
		OneWayObject->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		OneWayObject->AddInitComponent(new Collision());
		OneWayObject->AddInitComponent(new Sprite("asset/images/cannon_bullet.png"));

		Objectmanager_.AddObject(OneWayObject);
	}
	ImGui::SameLine();
	ImGui::Button("OneWay-Right");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* OneWayObject = new Object();
		OneWayObject->SetScale({ 50.0f, 50.0f });
		OneWayObject->SetTranslation(Input::GetMousePos());
		OneWayObject->AddInitComponent(new RigidBody());
		OneWayObject->GetComponentByTemplate<RigidBody>()->SetGravity(0);
		OneWayObject->AddComponent(new MovingObject(1.0f, OneWayObject->GetTransform().GetTranslation(), 100.0f, Direction::RIGHT, MovementType::ONEWAY, 2.0f));
		OneWayObject->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		OneWayObject->AddInitComponent(new Collision());
		OneWayObject->AddInitComponent(new Sprite("asset/images/cannon_bullet.png"));

		Objectmanager_.AddObject(OneWayObject);
	}
}

void Imgui_System::ObjectEditor(bool object_editor)
{
	if (!object_editor)
		return;

	if (selectObj == nullptr)
		return;

	selectObj->GetTransform().Imgui_Transform();

	if (selectObj->GetComponentByTemplate<Animation>() != nullptr)
		selectObj->GetComponentByTemplate<Animation>()->Imgui_Animation();

	SpriteHelper();

	if (ImGui::Button("Delete"))
	{
		for (auto object = Objectmanager_.GetObjectMap().begin(); object != Objectmanager_.GetObjectMap().end();)
		{
			if (object->get() == selectObj)
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

	ImGui::Separator();

	if (ImGui::RadioButton("Create Graphic Tile", graphics_tile))
	{
		graphics_tile = !graphics_tile;
	}

	ImGui::Text("If not selected, creates physical tile");

	ImGui::Separator();

	int i = 1;
	int j = 1;

	ImGui::Text("Non-Animated Tiles");
	ImGui::Separator();

	for (auto& temp : non_ani_tileList_buttons)
	{
		if (ImGui::ImageButton(temp.second, ImVec2(16, 16)))
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