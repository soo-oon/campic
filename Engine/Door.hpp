#pragma once
#include "Component.hpp"
#include <string>
#include "StateManager.hpp"

class Door : public Component
{
public:
    Door(std::string n_level) : next_level(n_level)
    {}
    ~Door();

    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;
    void SetLevel(std::string level) { next_level = level; }
    std::string GetLevel() { return next_level; }
private:
    std::string next_level;
};

