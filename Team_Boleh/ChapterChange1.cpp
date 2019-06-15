#include "ChapterChange1.hpp"
#include "StartCutScene.hpp"
#include "UI.hpp"

void ChapterChange1::Initialize()
{
    timer = 0.f;
    AudioManager_.LoadSong("asset/sounds/StartCutScene.mp3");
    AudioManager_.PlaySong("asset/sounds/StartCutScene.mp3");

    mouse_icon = new Object();
    mouse_icon->SetTranslation({ 0,0 });
    mouse_icon->SetScale({ 50,50 });
    mouse_icon->SetDepth(-0.9f);
    mouse_icon->SetObjectType(ObjectType::None);
    mouse_icon->SetMesh(mesh::CreateBox());
    mouse_icon->AddComponent(new Sprite("asset/images/UI/MouseCursor.png"));

    start = new Object();
    start->SetTranslation({ 0, 0 });
    start->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
    start->SetDepth(0.8f);
    start->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    start->SetObjectType(ObjectType::Background);
    start->AddComponent(new Sprite("asset/images/Page/DaytoEvening.png"));


    button = new Object();
    button->SetTranslation({ 700, -450 });
    button->SetScale({ 182,96 });
    button->SetDepth(HUD_BUTTON);
    button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    button->SetObjectType(ObjectType::Button);
    button->AddInitComponent(new Sprite("asset/images/UI/Skip.png"));
    button_.AddObject(button);

    Objectmanager_.AddObject(start);
    Objectmanager_.AddObject(mouse_icon);
}

void ChapterChange1::Update(float dt)
{
    timer += dt;

    mouse_icon->SetTranslation(Input::GetMousePos());

    if (timer >= 2.5f)
    {
        SetLevelIndicator("Level7");
        ChangeLevel("Level7");
    }


    if (Input::IsKeyAnyTriggered())
    {
        SetLevelIndicator("Level7");
        ChangeLevel("Level7");
    }

    if (button_.IntersectionCheck(Input::GetMousePos()))
    {
        button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
        if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
        {
            AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.3f);
            SetLevelIndicator("Level7");
            ChangeLevel("Level7");
            button_.RemoveContainer();
        }
    }
    else
    {
        for (auto&i : button_.GetContainer())
        {
            i.get()->GetMesh().ChangeColor({ 255, 255, 255 });
        }
    }
}

void ChapterChange1::ShutDown()
{
    UnLoad();
}
