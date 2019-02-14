/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Animation.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary : 
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "Component.hpp"
#include "Sprite.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include "vector2.hpp"
#include "imgui.h"
#include <algorithm>
#include <memory>

class Object;

class Animation_Information
{
public:
    Animation_Information() = default;

    Animation_Information(const std::string path_, /*std::string ID,*/ int image_frame_,
        float update_frame_, bool repeat = true)
        : path(path_), image_frames(image_frame_), update_frames(update_frame_), is_repeats(repeat)
    {
        sprites = new Sprite(false,path);

        frame_per_seconds = 1.0f / image_frames;
    };

    Sprite * sprites = nullptr;
	std::string path;
    int image_frames = 0;
    float update_frames = 0;
    float frame_per_seconds = 0;
    bool is_repeats = false;
    vector2 previous_current_coordinate{};
};

class Animation : public Component
{
public:
    Animation(std::string path_, std::string ID, int image_frame_, 
		float update_frame_, bool repeat = true )
    {
        current_animation = Animation_Information(path_, image_frame_, update_frame_, repeat);
		current_animation.sprites->Texture_Load();

        current_animation.previous_current_coordinate.x = 0;
		current_animation.previous_current_coordinate.y = current_animation.frame_per_seconds;

        animations.insert(std::make_pair(ID, current_animation));

    };

    bool Initialize(Object* Ob) override;
    void Update(float dt) override;

	void AddAnimaition(const std::string path, const std::string ID, 
		int image_frame_, float update_frame_, bool repeat = true);

    void Delete() override;

	void ChangeAnimation(std::string ID, std::string original_ID = NULL);

	bool IsDone() { return is_done; }

	void Imgui_Animation();

    Animation_Information GetCurrentAnimation() { return current_animation; }

private:
    Animation_Information current_animation;
	Animation_Information previous_animation;
    std::unordered_map<std::string, Animation_Information> animations;

	bool is_done = false;
    float frame_time = 0;
};
