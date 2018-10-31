#include "Animation.hpp"
#include "Object.hpp"
#include <iostream>
#include <cassert>

bool Animation::Initialize(Object* Ob)
{
    object = Ob;
    frame_per_second = (1.0f / image_frame);

    previous_current_coordinate.x = 0;
    previous_current_coordinate.y = frame_per_second;

    return true;
}

void Animation::Update(float dt)
{
    frame_time += dt;
    if (frame_time > update_frame)
    {
        if (frame_time == image_frame)
            frame_time = 0;

        ++frame_time;
        frame_time = 0;

        if (previous_current_coordinate.y < 1)
        {
            previous_current_coordinate.x += frame_per_second;
            previous_current_coordinate.y += frame_per_second;
        }
        else
        {
            previous_current_coordinate.x = 0;
            previous_current_coordinate.y = frame_per_second;
        }
    }
}

void Animation::AddAnimaition(const std::string path, const std::string ID, 
	int image_frame_, float update_frame_)
{
	sprites.insert(std::make_pair(ID, new Sprite()));
	sprites.at(ID)->Texture_Load(path);

	image_frames.insert(std::make_pair(ID, image_frame_));
	update_frames.insert(std::make_pair(ID, update_frame_));
	frame_per_seconds.insert(std::make_pair(ID, (1.0f / image_frames.find(ID)->second)));
}


//void Animation::AddAnimaition(const std::string path, const std::string ID)
//{
//	sprites.insert(std::make_pair(ID, new Sprite()));
//	sprites.at(ID)->Texture_Load(path);
//
//}

void Animation::Delete()
{
}

void Animation::ChangeAnimation(std::string ID)
{
	Sprite* change_animation = sprites.find(ID)->second;

	if (change_animation == nullptr)
		assert(false);

	current_sprite = change_animation;
	image_frame = image_frames.find(ID)->second;
	frame_per_second = frame_per_seconds.find(ID)->second;
	update_frame = update_frames.find(ID)->second;
}

void Animation::Imgui_Animation()
{
	ImGui::SliderFloat("frame_per_second", &frame_per_second, 0, 0.5);
	ImGui::SliderFloat("update_frame", &update_frame, 0.1, 0.01);
}
