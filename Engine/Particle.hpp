/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Particle.hpp
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
#include "vector2.hpp"
#include <memory>
#include <vector>

struct Particle_Obj
{
    float life_time;
    vector2 position;
    vector2 velocity;
};

class Particle : public Component
{
public:
    Particle(int number_, float life_time_)
    : number(number_)
    {
        for(int i = 0; i< number; ++i)
        {
        }
    };

    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;

private:
    std::vector<std::unique_ptr<Particle_Obj>> particles;
    int number;
    

};