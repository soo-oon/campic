#include "Animation.hpp"
#include "Object.hpp"
#include <iostream>

bool Animation::Initialize(Object* Ob)
{
    object = Ob;
    type = animation;
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

void Animation::Delete()
{
}
