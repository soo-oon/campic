#pragma once
#include "Component.hpp"
#include "Sprite.hpp"
#include <string>
#include <vector>
#include <map>
#include "vector2.hpp"
#include "imgui.h"
#include <algorithm>
#include <memory>

class Object;

class Animation : public Component
{
public:
    Animation(std::string path_, std::string ID, int image_frame_, 
		float update_frame_, bool repeat = true )
        : path(path_), update_frame(update_frame_), image_frame(image_frame_), isrepeat(repeat)
    {
		sprites.insert(std::make_pair(ID, new Sprite()));
		sprites.at(ID)->Texture_Load(path);
		current_sprite = sprites.at(ID);

		frame_per_second = (1.0f / image_frame);
		previous_current_coordinate.x = 0;
		previous_current_coordinate.y = frame_per_second;

		update_frames.insert(std::make_pair(ID, update_frame));
		image_frames.insert(std::make_pair(ID, image_frame));
		frame_per_seconds.insert(std::make_pair(ID, (1.0f / image_frame)));
		is_repeats.insert(std::make_pair(ID, isrepeat));
		previous_current_coordinates.insert(std::make_pair(ID, previous_current_coordinate));
    };

    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
	//void AddAnimaition(const std::string path, const std::string ID);
	void AddAnimaition(const std::string path, const std::string ID, 
		int image_frame_, float update_frame_, bool repeat = true);
    void Delete() override;
	void ChangeAnimation(std::string ID);

	Object* GetObject() { return object; }

	void Imgui_Animation();

    vector2 GetAnimationPosition() { return previous_current_coordinate; }
    Sprite* GetAnimationSprite() { return current_sprite; }

private:
    vector2 previous_current_coordinate{};
	//std::map<std::string, Animation*> animations;

	std::map<std::string, Sprite*> sprites;
	std::map<std::string, float> update_frames;
	std::map<std::string, float> frame_per_seconds;
	std::map<std::string, int> image_frames;
	std::map<std::string, bool> is_repeats;
	std::map<std::string, vector2> previous_current_coordinates{};

	Sprite* current_sprite = nullptr;
    std::string path;

    float frame_per_second = 0;
    float update_frame = 0;

	bool is_done = false;

    //float previous_position = 0;
    //float current_position = 0;
    float frame_time = 0;
    int image_frame = 0;
	bool isrepeat;
};
