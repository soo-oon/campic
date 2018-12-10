#include "Imgui_System.hpp"

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
	//glfwSetDropCallback();
	//ImGui_ImplGlfw_InstallCallbacks(window);

	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.FontDefault = NULL;
	io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos; 
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	for (auto& p : std::filesystem::directory_iterator("asset/images"))
	{
		imagelist.push_back(p.path().filename().string());
	}

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
		if (show_objectmanager_window)
			show_objectmanager_window = false;
		else
			show_objectmanager_window = true;
	}

	//ImGui::ShowTestWindow();
	ObjectManger(show_objectmanager_window);
	ImGui_Option(&show_demo_window);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	window = glfwGetCurrentContext();
	glfwSwapBuffers(window);
}

void Imgui_System::ObjectManger(bool show_window)
{
	if (!show_window)
	{
		if (object_manager != nullptr)
		{
			if (object_manager->GetObjectMap().size())
			{
				std::vector<std::string> object_lists;

				for (auto it = object_manager->GetObjectMap().begin();
					it != object_manager->GetObjectMap().end(); ++it)
				{
					object_lists.push_back((*it).first.c_str());
				}

				if (!ImGui::Begin("Object Manager", &show_window, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::End();
					return;
				}

				ImGui::Text("Team Boleh's GUI                                   ");

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
								
								if (temp->GetComponentByTemplate<Animation>() != nullptr)
								{
									temp->GetComponentByTemplate<Animation>()->Imgui_Animation();
								}

								if(temp->GetComponentByTemplate<Sprite>() != nullptr)
								{
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
									if (ImGui::Button("Add Sprite"))
									{
										temp->AddComponent(new Sprite());
										temp->GetComponentByTemplate<Sprite>()->Texture_Load(image_dir + current_item);
									}
								}
								if (ImGui::Button("Delete"))
								{
									object_manager->GetObjectMap().erase(object_lists.at(i).c_str());
								}
								ImGui::TreePop();
							}
						}
						ImGui::TreePop();
					}

					if (ImGui::Button("Create Object"))
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
	}
}

void Imgui_System::ImGui_Option(bool* show_window)
{
	ImGui::SetNextWindowSize({ 400,200 });
	if (!ImGui::Begin("ImGui Option", show_window))
	{
		ImGui::End();
		return;
	}

	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

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

	/*if (ImGui::Button("Create Sound"))
	{
		m_FMOD_system->CreateSound(current_path + current_sound);
	}

	if (ImGui::Button("Play"))
	{
		m_FMOD_system->Play();
	}

	ImGui::SameLine();
	if(ImGui::Button("Stop"))
	{
		if (m_FMOD_system->IsPlaying())
			m_FMOD_system->Stop();
	}

	ImGui::SameLine();
	if (ImGui::Button("Pause"))
	{
		if (m_FMOD_system->IsPlaying())
			m_FMOD_system->Pause();
	}

	static float i = 0;
	if(ImGui::SliderFloat("Volume", &i, 0, 10))
	{
		m_FMOD_system->SetVolume(i);
	}

	static float speed = 0;
	if (ImGui::SliderFloat("Speed", &speed, 0, 5))
	{
		m_FMOD_system->SetSoundSpeed(speed);
	}*/

	ImGui::End();
}
