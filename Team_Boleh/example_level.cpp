#include "example_level.hpp"
#include <iostream>

bool example::Initialize()
{
    return true;
}

void example::Update(float dt)
{
    std::cout << dt << std::endl;
}

void example::ShutDown()
{
}
