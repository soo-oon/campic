#pragma once
#include "Stage.hpp"

class example : public Stage
{
public:
    bool Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;
};