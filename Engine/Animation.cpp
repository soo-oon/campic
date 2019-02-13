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
    object = Ob;
    return true;
}

void Animation::Update(float dt)
{
	/*std::cout << object->GetTransform().GetTranslation().x << ", " << object->GetTransform().GetTranslation().y
		<< std::endl;*/

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

void Animation::AddAnimaition(const std::string path, const std::string ID,
	int image_frame_, float update_frame_, bool repeat)
{
    animations.insert(std::make_pair(ID, 
        Animation_Information(path, image_frame_, update_frame_, repeat)));
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

void Animation::Imgui_Animation()
{	
	//ImGui::SliderFloat("update_frame", &update_frame, 0.2f, 0.3f);
	//ImGui::SliderInt("image frame", &image_frame, 0, 20);
	//ImGui::SliderFloat("frame_per_second", &frame_per_second, 0.1f, 0.2f);
}
