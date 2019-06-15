#include "EndCutScene.hpp"
#include "Button.hpp"

void EndCutScene::Initialize()
{
     timer = 0.f;
     is_end_start_sprite = false;
     is_start_animation = false;

	AudioManager_.LoadSong("asset/sounds/EndCutScene.mp3");
	AudioManager_.PlaySong("asset/sounds/EndCutScene.mp3");

	mouse_icon = new Object();
	mouse_icon->SetTranslation({ 0,0 });
	mouse_icon->SetScale({ 50,50 });
	mouse_icon->SetDepth(-0.8f);
	mouse_icon->SetObjectType(ObjectType::None);
	mouse_icon->SetMesh(mesh::CreateBox());
	mouse_icon->AddComponent(new Sprite("asset/images/UI/MouseCursor.png"));

	start = new Object();
	start->SetTranslation({ 0, 0 });
	start->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	start->SetDepth(0.7f);
	start->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	start->SetObjectType(ObjectType::Background);
	start->AddComponent(new Sprite("asset/images/Page/WinPage.png"));
	start->GetMesh().Invisible();

	end = new Object();
	end->SetTranslation({ 0, 0 });
	end->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	end->SetDepth(0.6f);
	end->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	end->SetObjectType(ObjectType::Background);
	end->AddInitComponent(new Animation("asset/images/Page/EndCutScene1.png", "end1",11, 0.3f, false));


	end2 = new Object();
	end2->SetTranslation({ 0, 0 });
	end2->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	end2->SetDepth(0.6f);
	end2->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	end2->SetObjectType(ObjectType::Background);
	end2->AddInitComponent(new Animation("asset/images/Page/EndCutScene2.png", "end2", 15, 0.5f, false));
	end2->GetComponentByTemplate<Animation>()->SetIsActive(false);

	Object* button = new Object();
        button->SetTranslation({ 700, -450 });
	button->SetScale({ 182,96 });
	button->SetDepth(-0.5f);
	button->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	button->SetObjectType(ObjectType::Button);
	button->AddInitComponent(new Sprite("asset/images/UI/Skip.png"));

	Objectmanager_.AddObject(end);
	Objectmanager_.AddObject(end2);
	Objectmanager_.AddObject(start);
	Objectmanager_.AddObject(mouse_icon);
	button_.AddObject(button);
}

void EndCutScene::Update(float dt)
{
	timer += dt;

	mouse_icon->SetTranslation(Input::GetMousePos());

	if (!is_end_start_sprite)
	{
		if (timer >= 5.0f)
		{
			end->GetComponentByTemplate<Animation>()->SetIsActive(false);
			start->GetMesh().Visible();
			is_end_start_sprite = true;
		}
	}
	else
	{
		if (!is_start_animation)
		{
			if (timer >= 10.0f)
			{
				start->SetInvisible();
				end->GetMesh().Invisible();
				end2->GetComponentByTemplate<Animation>()->SetIsActive(true);
				is_start_animation = true;
			}
		}
	}

	if (is_start_animation)
	{
		if (timer >= 19.f)
		{
			SetLevelIndicator("Credit");
			StateManager_.ToCredit();
		}
	}

    if(Input::IsKeyAnyTriggered())
    {
        SetLevelIndicator("Credit");
        StateManager_.ToCredit();
    }

	if (button_.IntersectionCheck(Input::GetMousePos()))
	{
            button_.GetSelect().first->GetMesh().ChangeColor({ 255,255,0 });
		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			AudioManager_.PlaySFX("asset/sounds/Button.wav", 0.1f);

                        button_.RemoveContainer();
			SetLevelIndicator("Credit");
			StateManager_.ToCredit();
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

void EndCutScene::ShutDown()
{
	UnLoad();
	start = nullptr;
	end = nullptr;
	end2 = nullptr;
	mouse_icon = nullptr;
}
