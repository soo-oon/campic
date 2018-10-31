#include "Imgui_Setup.h"

bool Imgui_Setup::Initialize()
{
	//Imgui Setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	const char* glsl_version = "#version 300 es";
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.FontDefault = NULL;

	int w, h;
	glfwGetWindowSize(window, &w, &h);

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	return true;
}

void Imgui_Setup::Update(float dt)
{

}

void Imgui_Setup::Quit()
{
	ImGui::End();
}

void Imgui_Setup::Draw()
{
	ImGui::NewFrame();

	ImGui::ShowDemoWindow(&show_window);
	ObjectManger();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame();
}

void Imgui_Setup::ObjectManger()
{
	ImGui::Begin("Object Manager", &show_window, ImGuiWindowFlags_AlwaysAutoResize);
	const char* object_list[5] = {};

	int i = 0;
	for (std::map<std::string, std::unique_ptr<Object>>::iterator it = object_manager->GetObjectMap().begin();
		it != object_manager->GetObjectMap().end(); ++it)
	{
		object_list[i] = (*it).first.c_str();
		++i;
	}
	static const char* current_object = object_list[0];

	if (ImGui::BeginCombo("ObjectList", current_object))
	{
		for (int j = 0; j < IM_ARRAYSIZE(object_list); j++)
		{
			bool is_selected = (current_object == object_list[j]); // You can store your selection however you want, outside or inside your objects
			if (ImGui::Selectable(object_list[j], is_selected))
			{
				current_object = object_list[j];
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	if (object_manager->GetObjectMap().size())
	{
		object_manager->FindObject(current_object)->GetTransform().Imgui_Transform();
	}

	ImGui::End();
}