#pragma once
#include "Component.hpp"
#include "Sprite.hpp"
#include <string>
#include <vector>
#include "vector2.hpp"

class Object;

class Animation : public Component
{
public:
    Animation(int image_frame_, float update_frame_, std::string path_)
        : path(path_), update_frame(update_frame_), image_frame(image_frame_)
    {
        sprite = new Sprite();
        sprite->Texture_Load(path);
    };

    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;

    vector2 GetAnimationPosition() { return previous_current_coordinate; }
    Sprite* GetAnimationSprite() { return sprite; }

private:
    vector2 previous_current_coordinate{};
    Sprite* sprite = nullptr;
    std::string path;

    float frame_per_second = 0;
    float update_frame = 0;

    int image_frame = 0;

    float previous_position = 0;
    float current_position = 0;
    float frame_time = 0;
};
