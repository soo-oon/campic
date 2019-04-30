#pragma once
#include "Component.hpp"
#include "vector2.hpp"
#include "Object.hpp"

enum class TriggerStyle
{
    Door,
    Font,
    CheckPoint,
    None
};

class Trigger : public Component
{
public:
    Trigger(vector2 translation, TriggerStyle trigger_style) : o_translation(translation), m_trigger_style(trigger_style){}

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
    vector2 o_translation; //object_translation
    TriggerStyle m_trigger_style;
    Object* m_connected_object = nullptr;
    bool isTriggered = false;
};

