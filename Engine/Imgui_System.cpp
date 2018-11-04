#include "Imgui_System.hpp"

bool Imgui_System::Initialize()
{
	//Imgui Setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	const char* glsl_version = "#version 300 es";
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.FontDefault = NULL;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

	int w, h;
	glfwGetWindowSize(window, &w, &h);

	ImGui_ImplGlfw_InitForOpenGL(window, false);

	//ImGui_ImplGlfw_KeyCallback(window, );
	//ImGui_ImplGlfw_ScrollCallback(window);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

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

	ImGui::ShowDemoWindow(&show_window);
	ObjectManger();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	window = glfwGetCurrentContext();
	glfwSwapBuffers(window);
}

void Imgui_System::ObjectManger()
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

			if(!ImGui::Begin("Object Manager", &show_window, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::End();
				return;
			}
			ImGui::Text("Team Boleh's GUI");

			if(ImGui::CollapsingHeader("Manager"))
			{
				ImGuiIO& io = ImGui::GetIO();

				if(ImGui::TreeNode("Object Lists"))
				{
					for(int i = 0; i < object_lists.size(); i++)
					{
						if (ImGui::TreeNode(object_lists.at(i).c_str()))
						{
							object_manager->FindObject(object_lists.at(i).c_str())->GetTransform().Imgui_Transform();
							Object* temp = object_manager->FindObject(object_lists.at(i).c_str()).get();
							if (temp->GetComponentByTemplate<Animation>() != nullptr)
							{
								temp->GetComponentByTemplate<Animation>()->Imgui_Animation();
							}
							ImGui::TreePop();
						}
					}
					ImGui::TreePop();
				}

				if (ImGui::Button("Create Object"))
				{
					object_manager->AddObject("a");
					object_manager->FindObject("a").get()->SetMesh(mesh::CreateBox());
					object_manager->FindObject("a").get()->SetTranslation({ 100,100 });
					object_manager->FindObject("a").get()->SetScale({ 100,100 });
					//ImGui::PopID();
				}
			}
		}
		ImGui::End();
	}
}

namespace {

	void KeyCallback(GLFWwindow* window, int key, int scancode
		, int action, int mods)
	{
		Input::SetKeyPressed(key, action);
	}
}
