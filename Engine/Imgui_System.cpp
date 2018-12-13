#include "Imgui_System.hpp"
#include <iostream>
#include "Character.hpp"
#include "Graphics.hpp"
#include "status.hpp"

std::vector<std::string> Imgui_System::soundlist;

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
		imagelist.push_back(p.path().filename().string());
	}
	//Sound list in project directory
	for (auto& p : std::filesystem::directory_iterator("asset/sounds"))
	{
		soundlist.push_back(p.path().filename().string());
	}

	return true;
}

void Imgui_System::Update(float dt)
{

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

	if (Input::IsKeyTriggered(GLFW_KEY_TAB))
	{
		if (show_window)
			show_window = false;
		else
			show_window = true;
		show_editor = !show_editor;
	}
	object_count = object_manager->FindMaxID();

	ImGui::ShowDemoWindow(&show_window);
	//ImGui::ShowTestWindow();
	//ObjectManger(show_window);
	Sound_Option(show_window);
	Editor(show_editor);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	window = glfwGetCurrentContext();
	glfwSwapBuffers(window);
}

void Imgui_System::ObjectManger(bool show_window)
{
	if (!show_window)
		return;

	if (object_manager == nullptr)
		return;

	if (object_manager->GetObjectMap().size())
	{
		std::vector<std::string> object_lists;

		for (auto& obj : object_manager->GetObjectMap())
		{
			object_lists.push_back((obj).first.c_str());
		}

		ImGui::SetNextWindowSize({ 400, 400 });
		if (!ImGui::Begin("Object Manager", &show_window))
		{
			ImGui::End();
			return;
		}

		ImGui::Text("Team Boleh's GUI");

		if (ImGui::CollapsingHeader("Manager"))
		{
			ImGuiIO& io = ImGui::GetIO();

			if (ImGui::TreeNode("Object Lists"))
			{
				for (int i = 0; i < object_lists.size(); i++)
				{
					if (ImGui::TreeNode(object_lists.at(i).c_str()))
					{
						object_manager->FindObject(object_lists.at(i).c_str())->GetTransform().Imgui_Transform();
						Object* temp = object_manager->FindObject(object_lists.at(i).c_str()).get();

						//componentHelper(temp)
						
						if (ImGui::Button("Delete"))
						{
							object_manager->GetObjectMap().erase(object_lists.at(i).c_str());
						}
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}

			ImGui::Button("Create Object");
			
			if (ImGui::IsItemActive())
			{
				object_manager->AddObject(new_object);
				object_manager->FindObject(new_object).get()->SetMesh(mesh::CreateBox());
				object_manager->FindObject(new_object).get()->SetTranslation({ 100,100 });
				object_manager->FindObject(new_object).get()->SetScale({ 100,100 });
				new_object.at(6) += 1;
			}
			
		}
	}
	ImGui::End();
}

void Imgui_System::componentHelper(Object* object, ComponentType comp)
{
	static std::string current_item = "";
	std::string image_dir = "asset/images/";
	if (ImGui::BeginCombo("Select texture", current_item.c_str()))
	{
		for (int n = 0; n < imagelist.size(); n++)
		{
			bool is_selected = (current_item.c_str() == imagelist[n].c_str());
			if (ImGui::Selectable(imagelist[n].c_str(), is_selected))
				current_item = imagelist[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	//if(ImGui::BeginCombo("Select Component", ))

	if (ImGui::Button("Add Sprite"))
	{
		object->AddComponent(new Sprite());
		object->GetComponentByTemplate<Sprite>()->Texture_Load(image_dir + current_item);
	}

	switch(comp)
	{
	case ComponentType::Animation:
	{
		if(object->GetComponentByTemplate<Animation>() != nullptr)
		{
			object->GetComponentByTemplate<Animation>()->Imgui_Animation();
		}
		else
		{
			ImGui::Button("Add Animation");
			object->AddComponent(new Animation(image_dir + current_item, "", 0,0,true));
		}
		break;
	}
	case ComponentType::Sprite:
	{
		if (object->GetComponentByTemplate<Sprite>() != nullptr)
		{
			object->GetComponentByTemplate<Sprite>()->Imgui_Sprite();
		}
		else
		{
			ImGui::Button("Add Sprite");
			object->AddComponent(new Sprite);
			object->GetComponentByTemplate<Sprite>()->Texture_Load(image_dir + current_item);
		}
		break;
	}
	case ComponentType::Character:
	{
		break;
	}
	case ComponentType::RigidBody:
	{
		break;
	}
	case ComponentType::Collision:
	{
		break;
	}
	default:
		break;
	}
}

void Imgui_System::Sound_Option(bool show_window)
{
	if (!show_window)
		return;

	ImGui::SetNextWindowSize({ 400,200 });
	if (!ImGui::Begin("ImGui Option", &show_window))
	{
		ImGui::End();
		return;
	}

	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("Frame Rate (%.1f FPS)", io.Framerate);

	ImGui::Separator();
	ImGui::Text("Sound Option");

	static std::string current_sound = "";

	if (ImGui::BeginCombo("Select Sound", current_sound.c_str())) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < soundlist.size(); n++)
		{
			bool is_selected = (current_sound.c_str() == soundlist[n].c_str()); // You can store your selection however you want, outside or inside your objects
			if (ImGui::Selectable(soundlist[n].c_str(), is_selected))
				current_sound = soundlist[n].c_str();
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
		}
		ImGui::EndCombo();
	}

	const std::string current_path = "asset/sounds/";

	if (ImGui::Button("Create Sound"))
	{
		sound_manager->AddSound(current_path + current_sound);
	}

	if (ImGui::Button("Play"))
	{
		sound_manager->Play(current_path + current_sound);
	}

	ImGui::SameLine();
	if(ImGui::Button("Stop"))
	{
		if (sound_manager->IsPlaying())
			sound_manager->Stop(current_path + current_sound);
	}

	ImGui::SameLine();
	if (ImGui::Button("Pause"))
	{
		if (sound_manager->IsPlaying())
			sound_manager->Pause(current_path + current_sound);
	}

	static float i = 0;
	if(ImGui::SliderFloat("Volume", &i, 0, 10))
	{
		sound_manager->SetVolume(i);
	}

	static float speed = 0;
	if (ImGui::SliderFloat("Speed", &speed, 0, 5))
	{
		sound_manager->SetSoundSpeed(current_path + current_sound, speed);
	}

	ImGui::End();
}

//////////////////////////////////////////////////////////
void Imgui_System::Editor(bool show_editor)
{
	if (!show_editor)
		return;
	
	if (object_manager == nullptr)
		return;

	std::vector<std::string> object_lists;

	for (auto& obj : object_manager->GetObjectMap())
		object_lists.push_back((obj).first.c_str());

	if (!ImGui::Begin("Object Manager", &show_editor, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
		return;
	}

	ImGui::Text("Team Boleh's GUI                                              ");

	if (ImGui::CollapsingHeader("Manager"))
	{
		ImGuiIO& io = ImGui::GetIO();

		if (ImGui::TreeNode("Object Lists"))
		{
			AllObjectTree(object_lists);
			ImGui::TreePop();
		}

		ImGui::Button("Create Object");
		if (ImGui::IsItemActive())
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		}
		if (ImGui::IsItemDeactivated())
		{
			std::string new_obj_name = object_name + std::to_string(object_count + 1);
			object_manager->AddObject(new_obj_name);
			newObject = object_manager->FindObject(new_obj_name).get();
			newObject->SetScale({ 100.f,100.f });
			newObject->SetTranslation({ Input::GetMousePos(Graphics::checking_zoom).x, Input::GetMousePos(Graphics::checking_zoom).y });
			newObject->SetDepth(0);
			newObject->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
			newObject->object_id = object_count + 1;
			object_count++;
		}
		ImGui::SameLine();
		if (ImGui::Button("Clear All"))
		{
			for (int i = 0; i < object_lists.size(); i++)
			{
				if (object_lists.at(i) == "background")
					continue;
				if (object_lists.at(i) == "Player")
					continue;
				if (object_lists.at(i) == "Sword")
					continue;
				object_manager->FindObject(object_lists.at(i))->GetMesh().Invisible();
			}
		}
	}
	ImGui::End();
}

void Imgui_System::AllObjectTree(std::vector<std::string> obj_list)
{
	for (int i = 0; i < obj_list.size(); i++)
	{
		Object* temp = object_manager->FindObject(obj_list.at(i).c_str()).get();
		if (!temp->GetMesh().IsVisible())
			continue;
		if (obj_list.at(i) == "displaybox") //this is the display box at map editor
			continue;

		if (ImGui::TreeNode(obj_list.at(i).c_str())) //um... update new!
		{
			temp->GetTransform().Imgui_Transform();

			ObjectSprite(temp);
			ObjectAnimation(temp);
			ObjectCharacter(temp);

			ImGui::TreePop();
			if (ImGui::Button("Delete"))
				temp->GetMesh().Invisible();
		}
	}
}

void Imgui_System::ObjectSprite(Object* obj)
{
	if (ImGui::TreeNode("Sprite"))
	{
		if (obj->GetComponentByTemplate<Sprite>() == nullptr)
		{
			static std::string current_item = "";
			std::string image_dir = "asset/images/";
			if (ImGui::BeginCombo("Select Sprite", current_item.c_str()))
			{
				for (int n = 0; n < imagelist.size(); n++)
				{
					bool is_selected = (current_item.c_str() == imagelist[n].c_str());
					if (ImGui::Selectable(imagelist[n].c_str(), is_selected))
						current_item = imagelist[n].c_str();
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			if (ImGui::Button("Add Sprite"))
			{
				obj->AddComponent(new Sprite());
			}
		}
		else
		{
			static std::string current_item = "";
			std::string image_dir = "asset/images/";
			if (ImGui::BeginCombo("Select texture", current_item.c_str()))
			{
				for (int n = 0; n < imagelist.size(); n++)
				{
					bool is_selected = (current_item.c_str() == imagelist[n].c_str());
					if (ImGui::Selectable(imagelist[n].c_str(), is_selected))
						current_item = imagelist[n].c_str();
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			if (ImGui::Button("Change Sprite"))
			{
				obj->GetComponentByTemplate<Sprite>()->Texture_Load(image_dir + current_item);
				obj->texture_path = image_dir + current_item;
			}
		}
		ImGui::TreePop();
	}
}

void Imgui_System::ObjectAnimation(Object* obj)
{
	if (ImGui::TreeNode("Animation"))
	{
		if (obj->GetComponentByTemplate<Animation>() == nullptr)
		{
			static std::string current_item = "";
			std::string image_dir = "asset/images/";
			if (ImGui::BeginCombo("Select Animation", current_item.c_str()))
			{
				for (int n = 0; n < imagelist.size(); n++)
				{
					bool is_selected = (current_item.c_str() == imagelist[n].c_str());
					if (ImGui::Selectable(imagelist[n].c_str(), is_selected))
						current_item = imagelist[n].c_str();
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			if (ImGui::Button("Add Animation"))
			{
				obj->AddComponent(new Animation(image_dir+current_item, " ", 4, 0.2f, true));
				obj->texture_path = image_dir + current_item;
			}
		}
		else
		{
			static std::string current_item = "";
			std::string image_dir = "asset/images/";
			if (ImGui::BeginCombo("Select Animation", current_item.c_str()))
			{
				for (int n = 0; n < imagelist.size(); n++)
				{
					bool is_selected = (current_item.c_str() == imagelist[n].c_str());
					if (ImGui::Selectable(imagelist[n].c_str(), is_selected))
						current_item = imagelist[n].c_str();
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			obj->GetComponentByTemplate<Animation>()->Imgui_Animation();
		}
		ImGui::TreePop();
	}
}

void Imgui_System::ObjectCharacter(Object* obj)
{
	if(ImGui::TreeNode("Character Type"))
	{
		if(obj->GetComponentByTemplate<Character>() == nullptr)
		{
			if(ImGui::Button("Add Object Type"))
			{
				obj->AddComponent(new Character(ObjectType::none));
			}
		}
		else
		{
			const char* type_list[8] = { "player", "opponent", "sword", "wall", "card","door","shot","none" };
			static std::string current_item = "";
			if (ImGui::BeginCombo("Select Collision Type", current_item.c_str()))
			{
				for (int n = 0; n < 8; n++)
				{
					bool is_selected = (current_item.c_str() == type_list[n]);
					if (ImGui::Selectable(type_list[n], is_selected))
					{
						current_item = type_list[n];
					}
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			if (ImGui::Button("Change Collision Type"))
			{
				if (current_item == "player")
				{
					obj->GetComponentByTemplate<Character>()->SetCharType(ObjectType::player);
				}
				if (current_item == "opponent")
				{
					obj->GetComponentByTemplate<Character>()->SetCharType(ObjectType::opponent);
				}
				if (current_item == "sword")
				{
					obj->GetComponentByTemplate<Character>()->SetCharType(ObjectType::sword);
				}
				if (current_item == "wall")
				{
					obj->GetComponentByTemplate<Character>()->SetCharType(ObjectType::wall);
				}
				if (current_item == "card")
				{
					obj->GetComponentByTemplate<Character>()->SetCharType(ObjectType::card);
				}
				if (current_item == "door")
				{
					obj->GetComponentByTemplate<Character>()->SetCharType(ObjectType::door);
				}
				if (current_item == "shot")
				{
					obj->GetComponentByTemplate<Character>()->SetCharType(ObjectType::shot);
				}
				if (current_item == "none")
				{
					obj->GetComponentByTemplate<Character>()->SetCharType(ObjectType::none);
				}
				obj->AddComponent(new Status());
			}
		}


		if (ImGui::TreeNode("Collision"))
		{
			int count = 0;

			const char* collision_list[3] = { "box", "circle", "triangle" };
			static std::string current_item = "";
			if (ImGui::BeginCombo("Select Collision Type", current_item.c_str()))
			{
				for (int n = 0; n < 3; n++)
				{
					bool is_selected = (current_item.c_str() == collision_list[n]);
					if (ImGui::Selectable(collision_list[n], is_selected))
					{
						current_item = collision_list[n];
						count = n;
					}
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			ImGui::SameLine();
			ImGui::Text("Collision Type");

			if (obj->GetComponentByTemplate<Collision>() == nullptr)
			{
				if (ImGui::Button("Add Collision Type"))
				{
					obj->AddComponent(new Collision());
				}
			}
			else
			{
				if (ImGui::Button("Change Collision Type"))
				{
					if (count == 0)
					{
						obj->GetComponentByTemplate<Collision>()->SetCollisionType(box_);
					}
					if (count == 1)
					{
						obj->GetComponentByTemplate<Collision>()->SetCollisionType(circle_);
					}
					if (count == 2)
					{
						obj->GetComponentByTemplate<Collision>()->SetCollisionType(triangle_);
					}
				}
			}
			ImGui::TreePop();
		}
	ImGui::TreePop();
	}
}