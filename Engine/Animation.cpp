/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Animation.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#include "Animation.hpp"
#include "Object.hpp"
#include <iostream>
#include <cassert>

bool Animation::Initialize(Object* Ob)
{
	if (object == nullptr)
	{
		object = Ob;
	}
    return true;
}

void Animation::Update(float dt)
{
	if (isactive)
	{
		frame_time += dt;

		if (frame_time > current_animation.update_frames)
		{
			frame_time = 0;

			if (current_animation.previous_current_coordinate.y < 1)
			{
				current_animation.previous_current_coordinate.x += current_animation.frame_per_seconds;
				current_animation.previous_current_coordinate.y += current_animation.frame_per_seconds;
			}
			else
			{
				is_done = true;

				if (current_animation.is_repeats)
				{
					current_animation.previous_current_coordinate.x = 0;
					current_animation.previous_current_coordinate.y = current_animation.frame_per_seconds;
				}
				else
				{
					current_animation = previous_animation;
				}
			}
		}
	}
}

void Animation::AddAnimaition(const std::string path, const std::string ID,
	int image_frame_, float update_frame_, bool repeat)
{
    animations.insert(std::make_pair(ID, 
        Animation_Information(path, ID, image_frame_, update_frame_, repeat)));
}

void Animation::Delete()
{
}

void Animation::ChangeAnimation(std::string ID, std::string original_ID)
{
	if (!original_ID.empty())
		previous_animation = animations.find(original_ID)->second;

	if(current_animation.is_repeats)
	{
		current_animation = animations.find(ID)->second;
		current_animation.sprites->Texture_Load();

		current_animation.previous_current_coordinate.x = 0;
		current_animation.previous_current_coordinate.y = current_animation.frame_per_seconds;
	}
}

void Animation::SetIsActive(bool condition)
{
	isactive = condition;
}

void Animation::Imgui_Animation()
{	
	if (ImGui::TreeNode("Animation"))
	{
		ImGui::InputFloat("update_frame", &current_animation.update_frames, 0.f, 1.f);
		ImGui::InputInt("image frame", &current_animation.image_frames, 0, 20);

		ImGui::TreePop();
	}

	
}
