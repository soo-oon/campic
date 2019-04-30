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
#include "stb_image.h"
#include <imgui_internal.h>
#include "Tile_Map.hpp"
#include "Physics.hpp"
#include "Capture.hpp"
#include "MovingObject.hpp"
#include "Projectile.hpp"
#include "UI.hpp"
#include "Level.hpp"
#include "Trigger.h"

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
	//Sound list in project directory
	for (auto& p : std::filesystem::directory_iterator("asset/sounds"))
	{
		soundList.push_back(p.path().filename().string());
	}
	//Tile list in project directory
	for (auto& p : std::filesystem::directory_iterator("asset/images/Tiles"))
	{
		non_ani_tileList.push_back(non_ani_tile_dir + p.path().filename().string());
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
		selectObj = nullptr;
	}

	if (show_window)
	{
		glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);

		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			if(!selectObj)
				selectObj = Input::ImGuiObjectClicker();
		}

		if (Input::IsMouseDoubleClicked(GLFW_MOUSE_BUTTON_LEFT))
		{
			selectObj = nullptr;
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
        player_existed = false;
        start_existed = false;
        capture_existed = false;
        Tile_Map_.MakeGridFalse();
		Physics_.ResetPreviousSize();
                Object* camera = new Object;
                camera->SetObjectType(ObjectType::Camera);
                camera->AddComponent(new Camera("Level"));
                Objectmanager_.AddObject(camera);
	}

	if (ImGui::Button("Clear Graphic Tiles"))
	{
		Tile_Map_.ClearGraphicTiles();
	}

	if (ImGui::Button("Clear Physical Tiles"))
	{
		Tile_Map_.ClearPhysicalTiles();
	}

	if(ImGui::Button("Clear Objects"))
	{
		Objectmanager_.GetObjectMap().clear();
                Object* camera = new Object;
                camera->SetObjectType(ObjectType::Camera);
                camera->AddComponent(new Camera("Level"));
                Objectmanager_.AddObject(camera);
	}

	ImGui::End();
}

void Imgui_System::ObjectCreator(bool object_creator)
{
	if (!object_creator)
		return;

	ImGui::Text("Archetype");
	ImGui::Separator();

	ImGui::Button("Start Pos");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		for (auto obj : Objectmanager_.GetObjectMap())
		{
			if (obj.get()->GetObjectType() == ObjectType::Start_Pos)
				start_existed = true;
		}
	}
	if (ImGui::IsItemDeactivated())
	{
		if (!start_existed)
		{
			Object* s_pos = new Object();
			s_pos->SetTranslation(Input::GetMousePos());
			s_pos->SetScale({ 75.0f, 75.0f });
			s_pos->SetMesh(mesh::CreateBox(1, { 0,255,255, 255 }));
			s_pos->SetDepth(GAME_OBJECT);
			s_pos->SetObjectType(ObjectType::Start_Pos);

			Objectmanager_.AddObject(s_pos);
		}
	}

	ImGui::SameLine();

	ImGui::Button("Reset Pos");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}
	if (ImGui::IsItemDeactivated())
	{
		if (!start_existed)
		{
			Object* r_pos = new Object();
			r_pos->SetTranslation(Input::GetMousePos());
			r_pos->SetScale({ 75.0f, 75.0f });
			r_pos->SetMesh(mesh::CreateBox(1, { 255,255,255, 255 }));
			r_pos->SetDepth(GAME_OBJECT);
			r_pos->SetObjectType(ObjectType::Reset_Pos);
			r_pos->AddComponent(new Collision(box_));
			r_pos->AddComponent(new Animation("asset/images/Cameraman.Png", "cameraman", 3, 0.01f));

			Objectmanager_.AddObject(r_pos);
		}
	}

	ImGui::Text("Type target Level");
	static char buffer[100] = "";
	ImGui::InputText("", buffer, IM_ARRAYSIZE(buffer));

	ImGui::SameLine();
	if (ImGui::Button("Reset"))
	{
		memset(buffer, 0, 100);
	}

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
		door->SetDepth(GAME_OBJECT);
		door->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
		door->SetObjectType(ObjectType::Door);
		door->AddInitComponent(new Collision(box_));
		door->AddInitComponent(new Animation("asset/images/Portal.png", "portal", 9, 0.01f));
		door->AddComponent(new UI(buffer));

		Objectmanager_.AddObject(door);
	}

	ImGui::SameLine();
	ImGui::Button("Photo Zone");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	if (ImGui::IsItemDeactivated())
	{
		Object* zone = new Object();
		zone->SetTranslation(Input::GetMousePos());
		zone->SetScale({ 100, 100 });
		zone->SetDepth(GAME_OBJECT);
		zone->SetMesh(mesh::CreateBox(1, { 255,255,255,150 }));
		zone->SetObjectType(ObjectType::Door);
		zone->AddInitComponent(new Animation("asset/images/PhotoZone.png","zone",4, 0.05f));

		Objectmanager_.AddObject(zone);
	}

	ImGui::Separator();

    ImGui::Text("Trigger Pos");
	static vector2 pos;
	ImGui::InputFloat("x", &pos.x, -1000.f, 2000.0f);
	ImGui::InputFloat("y", &pos.y, -1000.f, 2000.0f);

        ImGui::Text("Text");
        static char buf_text[100] = "";
        ImGui::InputText(" ", buf_text, IM_ARRAYSIZE(buf_text));

        ImGui::SameLine();
        if (ImGui::Button("Reset"))
        {
            memset(buf_text, 0, 100);
        }

	const char* trigger_type[] = { "CheckPoint","Door", "Font", "None" };
	static int item_current = 0;
	ImGui::Combo("Select Trigger Type", &item_current, trigger_type, IM_ARRAYSIZE(trigger_type));

	//여기다가 저 vector pos 값 오브젝트에넣고 item current 값을 static_cast<니 트리거 타입>으로 형변환해서 박으셈 
	//밑에는 알아서 바꾸고
        ImGui::Button("Trigger");
	if (ImGui::IsItemActive())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}
        
	if (ImGui::IsItemDeactivated())
	{
		Object* trigger = new Object();
                trigger->SetTranslation(Input::GetMousePos());
                trigger->SetScale({ 10,100 });
                trigger->SetDepth(GAME_OBJECT);
                trigger->SetObjectType(ObjectType::Trigger);
                trigger->SetMesh(mesh::CreateBox());
                trigger->AddInitComponent(new Collision(box_));
                trigger->AddInitComponent(new Trigger(pos, static_cast<TriggerStyle>(item_current), buf_text));

		Objectmanager_.AddObject(trigger);
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
		cannon->SetDepth(GAME_OBJECT);
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
		weapon->SetDepth(GAME_OBJECT);
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
		RoundObject->SetObjectType(ObjectType::Item_Dynamic);
		RoundObject->AddComponent(new MovingObject(100.0f, RoundObject->GetTransform().GetTranslation(), 300.0f, Direction::DOWN, MovementType::ROUND, 0.0f));
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
		RoundObject->SetObjectType(ObjectType::Item_Dynamic);
		RoundObject->AddComponent(new MovingObject(100.0f, RoundObject->GetTransform().GetTranslation(), 300.0f, Direction::UP, MovementType::ROUND, 0.0f));
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
		RoundObject->SetObjectType(ObjectType::Item_Dynamic);
		RoundObject->AddComponent(new MovingObject(100.0f, RoundObject->GetTransform().GetTranslation(), 100.0f, Direction::LEFT, MovementType::ROUND, 0.0f));
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
		RoundObject->SetObjectType(ObjectType::Item_Dynamic);
		RoundObject->AddComponent(new MovingObject(100.0f, RoundObject->GetTransform().GetTranslation(), 300.0f, Direction::RIGHT, MovementType::ROUND, 0.0f));
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
		OneWayObject->SetObjectType(ObjectType::Item_Dynamic);
		OneWayObject->AddComponent(new MovingObject(100.0f, OneWayObject->GetTransform().GetTranslation(), 300.0f, Direction::DOWN, MovementType::ONEWAY, 5.0f));
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
		OneWayObject->SetObjectType(ObjectType::Item_Dynamic);
		OneWayObject->AddComponent(new MovingObject(100.0f, OneWayObject->GetTransform().GetTranslation(), 300.0f, Direction::UP, MovementType::ONEWAY, 0.0f));
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
		OneWayObject->SetObjectType(ObjectType::Item_Dynamic);
		OneWayObject->AddComponent(new MovingObject(100.0f, OneWayObject->GetTransform().GetTranslation(), 300.0f, Direction::LEFT, MovementType::ONEWAY, 3.0f));
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
		OneWayObject->SetObjectType(ObjectType::Item_Dynamic);
		OneWayObject->AddComponent(new MovingObject(100.0f, OneWayObject->GetTransform().GetTranslation(), 300.0f, Direction::RIGHT, MovementType::ONEWAY, 2.0f));
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
		for (auto object = Objectmanager_.GetObjectMap().begin(); object != Objectmanager_.GetObjectMap().end();++object)
		{
			if (object->get() == selectObj)
			{
				object = Objectmanager_.GetObjectMap().erase(object);
				selectObj = nullptr;
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
			for (size_t n = 0; n < imageList.size(); n++)
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