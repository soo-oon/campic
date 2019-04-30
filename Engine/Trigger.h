#pragma once
#include "Component.hpp"
#include "vector2.hpp"
#include "Object.hpp"

enum class TriggerStyle
{
    CheckPoint,
    Door,
    Font,
    None
};

class Trigger : public Component
{
public:
    Trigger(vector2 translation, TriggerStyle trigger_style, std::string string = " ", bool istriggered = false) : o_translation(translation), m_trigger_style(trigger_style)
    {
        isTriggered = istriggered;
        text = string;
    }

    bool Initialize(Object* Ob);
    void Update(float dt);
    void Delete();

public:
    //When you make function and style, input in this function.
    void ConnectObjectAction();

    void SetIsTriggerd(bool trigger) { isTriggered = trigger; }
    void SetTriggerStyle(TriggerStyle trigger) { m_trigger_style = trigger; }
    void SetObjectTranslation(vector2 obj) { o_translation = obj;}
    void SetConnectedObject(Object* obj) { m_connected_object = obj;}
    void SetText(std::string obj) { text = obj;}

    std::string GetText() { return text; }
    bool GetIsTriggerd() { return isTriggered; }
    Object* GetConnectedObject() { return m_connected_object; }
    TriggerStyle GetTriggerStyle() { return m_trigger_style; }
    vector2 GetObjectTranslation() { return o_translation; }
private:

    //When you want to use trigger, you should make Triggerstyle and function that you want to apply.
    //When you make new item, item ObjectType must be Trigger_Obj.
    //If you want to make Trigger_Obj, you can use translation
    void MakeConnectedDoor();
    void CheckPoint();
    void Text();
    std::string text;
    vector2 o_translation; //object_translation
    TriggerStyle m_trigger_style;
    bool isTriggered;
    Object* m_connected_object = nullptr;
};

