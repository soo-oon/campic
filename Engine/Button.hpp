#pragma once
#include <vector>
#include "Object.hpp"


enum class CollisionState
{
    Collided,
    NotCollided,
    WasCollided,
};

class Button
{
public:

    void AddObject(Object* obj);
    void AddObject(std::shared_ptr<Object> obj);
    void RemoveContainer() { m_button_container.clear(); }
    std::vector<std::shared_ptr<Object>> GetContainer() { return m_button_container; }
    
    std::pair<Object*, CollisionState>& GetSelect() { return m_selected_object; }
    
    bool IntersectionCheck(vector2 mouse_pos);
    

private:
    std::pair<Object*, CollisionState> m_selected_object = { nullptr, CollisionState::NotCollided };
    std::vector<std::shared_ptr<Object>> m_button_container;
};


extern Button button_;