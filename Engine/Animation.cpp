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
    frame_time += dt;

	if (frame_time > update_frame)
	{
		frame_time = 0;

		if (previous_current_coordinate.y < 1)
		{
			previous_current_coordinate.x += frame_per_second;
			previous_current_coordinate.y += frame_per_second;
		}
		else
		{
			if (isrepeat)
			{
				previous_current_coordinate.x = 0;
				previous_current_coordinate.y = frame_per_second;
			}
			else
			{
				is_done = true;
			}
		}
	}
}

void Animation::AddAnimaition(const std::string path, const std::string ID,
	int image_frame_, float update_frame_, bool repeat)
{
	sprites.insert(std::make_pair(ID, new Sprite()));
	sprites.at(ID)->Texture_Load(path);

	float temp_frame_per_second = (1.0f / image_frame_);
	vector2 temp_previous_current_coordinate;

	temp_previous_current_coordinate.x = 0;
	temp_previous_current_coordinate.y = temp_frame_per_second;

	image_frames.insert(std::make_pair(ID, image_frame_));
	update_frames.insert(std::make_pair(ID, update_frame_));
	frame_per_seconds.insert(std::make_pair(ID, temp_frame_per_second));
	is_repeats.insert(std::make_pair(ID, repeat));
	previous_current_coordinates.insert(std::make_pair(ID, temp_previous_current_coordinate));
}

void Animation::Delete()
{
}

void Animation::ChangeAnimation(std::string ID)
{
    if (isrepeat)
    {
        Sprite* change_animation = sprites.find(ID)->second;

        if (change_animation == nullptr)
            assert(false);

        if (current_sprite != change_animation)
        {
            current_sprite = change_animation;
            image_frame = image_frames.find(ID)->second;
            frame_per_second = frame_per_seconds.find(ID)->second;
            update_frame = update_frames.find(ID)->second;
            isrepeat = is_repeats.find(ID)->second;
            previous_current_coordinate = previous_current_coordinates.find(ID)->second;
        }
    }
    else
    {
        if(is_done)
        {
            Sprite* change_animation = sprites.find(ID)->second;

            if (change_animation == nullptr)
                assert(false);

            if (current_sprite != change_animation)
            {
                is_done = false;
                current_sprite = change_animation;
                image_frame = image_frames.find(ID)->second;
                frame_per_second = frame_per_seconds.find(ID)->second;
                update_frame = update_frames.find(ID)->second;
                isrepeat = is_repeats.find(ID)->second;
                previous_current_coordinate = previous_current_coordinates.find(ID)->second;
            }
        }
    }
}

void Animation::Imgui_Animation()
{	
	ImGui::SliderFloat("frame_per_second", &frame_per_second, 0, 0.5);
	ImGui::SameLine();
	ImGui::Text("Animation");
	ImGui::SliderFloat("update_frame", &update_frame, 0.1f, 0.01f);
}
