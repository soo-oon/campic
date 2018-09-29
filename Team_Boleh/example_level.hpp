#pragma once
#include "test.hpp"
#include "Stage.hpp"
#include "Object.hpp"

class example : public State
{
public:
    bool Initialize() override;
    void Update(float dt) override;
    void ShutDown() override;

	Object temp;
private:
};