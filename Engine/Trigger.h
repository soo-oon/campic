#pragma once
#include "Component.hpp"
#include "vector2.hpp"

enum class TriggerStyle
{
    Door,
    Font,
    None
};

class Trigger : public Component
{
public:
    Trigger(vector2 translation) : o_translation(translation){}

    bool Initialize(Object* Ob);
    void Update(float dt);
    void Delete();

public:
    //When you make function and style, input in this function.
    void ConnectObjectAction();

    void SetIsTriggerd(bool trigger) { isTriggered = trigger; }
    void SetObjectTranslation(vector2 obj) { o_translation = obj;}

    bool GetIsTriggerd() { return isTriggered; }
    vector2 GetObjectTranslation() { return o_translation; }
private:

    //When you want to use trigger, you should make Triggerstyle and function that you want to apply.
    //When you make new item, item ObjectType must be Trigger_Obj.
    //If you want to make Trigger_Obj, you can use translation

    TriggerStyle m_trigger_style = TriggerStyle::None;
    vector2 o_translation;
    bool isTriggered = false;
};

