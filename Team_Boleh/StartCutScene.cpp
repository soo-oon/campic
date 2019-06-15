#include "StartCutScene.hpp"
#include "UI.hpp"

void StartCutScene::Initialize()
{
    timer = 0.f;
    is_end_start_sprite = false;
    is_start_animation = false;
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
	start->SetDepth(0.6f);
	start->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	start->SetObjectType(ObjectType::Background);
	start->AddComponent(new Sprite("asset/images/Page/Start1.png"));

	start1 = new Object();
	start1->SetTranslation({ 0, 0 });
	start1->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	start1->SetDepth(0.6f);
	start1->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	start1->SetObjectType(ObjectType::Background);
	start1->AddInitComponent(new Animation("asset/images/Page/StartCutScene.png", "cut", 20, 0.1f, false));
	start1->GetComponentByTemplate<Animation>()->SetIsActive(false);

	button = new Object();
    button->SetTranslation({ Application_.GetScreenSize().x / 2, -Application_.GetScreenSize().y / 2  });
	button->SetScale({182,96});
	button->SetDepth(HUD_BUTTON);
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::Button);
	button->AddInitComponent(new Sprite("asset/images/UI/BackButton.png"));
	button_.AddObject(button);

	Objectmanager_.AddObject(start);
	Objectmanager_.AddObject(start1);
	Objectmanager_.AddObject(mouse_icon);
}

void StartCutScene::Update(float dt)
{
	timer += dt;

	mouse_icon->SetTranslation(Input::GetMousePos());

	if (!is_end_start_sprite)
	{
		if (timer >= 3.0f)
		{
			start->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/Page/Start2.png");
			is_end_start_sprite = true;
		}
	}
	else
	{
		if(!is_start_animation)
		{
			if (timer >= 6.0f)
			{
				start->SetInvisible();
				start1->GetComponentByTemplate<Animation>()->SetIsActive(true);
				is_start_animation = true;
			}
		}
	}

	if(is_start_animation)
	{
		if(start1->GetComponentByTemplate<Animation>()->IsDone())
		{
			SetLevelIndicator("Level1");
			ChangeLevel("Level1");
		}
	}

    if(Input::IsKeyAnyTriggered())
    {
        SetLevelIndicator("Level1");
        ChangeLevel("Level1");
    }

	if (button_.IntersectionCheck(Input::GetMousePos()))
	{
            button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
                    AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.3f);
                    SetLevelIndicator("Level1");
                    ChangeLevel("Level1");
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

void StartCutScene::ShutDown()
{
	UnLoad();
}
