#pragma once
#include "Component.hpp"
#include "Sprite.hpp"
#include <string>
#include <vector>
#include <map>
#include "vector2.hpp"
#include <algorithm>
#include <memory>
#include "imgui.h"

class Object;

class Animation : public Component
{
public:
    Animation(int image_frame_, float update_frame_, std::string path_, std::string ID)
        : path(path_), update_frame(update_frame_), image_frame(image_frame_)
    {
		sprites.insert(std::make_pair(ID, new Sprite()));
		sprites.at(ID)->Texture_Load(path);
		current_sprite = sprites.at(ID);
    };

    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
	void AddAnimaition(const std::string path, const std::string ID);
    void Delete() override;
	void ChangeAnimation(std::string ID);

    vector2 GetAnimationPosition() { return previous_current_coordinate; }
    Sprite* GetAnimationSprite() { return current_sprite; }

	void Imgui_Animation();
private:
    vector2 previous_current_coordinate{};
	std::map<std::string, Sprite*> sprites;
	Sprite* current_sprite = nullptr;
    std::string path;

    float frame_per_second = 0;
    float update_frame = 0;

    int image_frame = 0;

    float previous_position = 0;
    float current_position = 0;
    float frame_time = 0;
};
