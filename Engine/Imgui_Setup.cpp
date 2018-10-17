#include "Imgui_Setup.h"

void Imgui_Setup::ObjectManager(Objectmanager* object_manager, bool* open)
{
	if (!ImGui::Begin("Object Manager", open))
	{
		ImGui::End();
		return;
	}

	const char* object_list[100] = { 0 };

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
		for (int j = 0; j < i; j++)
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

	object_manager->FindObject(current_object)->GetTransform().Imgui_Transform();
	if(object_manager->FindObject(current_object)->GetComponentByTemplate<Animation>() != nullptr)
		object_manager->FindObject(current_object)->GetComponentByTemplate<Animation>()->Imgui_Animation();

	ImGui::End();
}
