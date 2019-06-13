#include "StartCutScene.hpp"

void StartCutScene::Initialize()
{
    check = new Object();
    check->SetTranslation({ 0, 0 });
    check->SetScale({100,100});
    check->SetDepth(-0.6f);
    check->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    check->SetObjectType(ObjectType::Bus);
    check->AddComponent(new Sprite("asset/images/Page/Start1.png"));

    check1 = new Object();
    check1->SetTranslation({ 300, 300 });
    check1->SetScale({ 100,100});
    check1->SetDepth(-0.6f);
    check1->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
    check1->SetObjectType(ObjectType::Bus);
    check1->AddComponent(new Sprite("asset/images/Page/Start.png"));

    button_.AddObject(check1);
    button_.AddObject(check);
    
 //   timer = 0.f;
 //   is_end_start_sprite = false;
 //   is_start_animation = false;
	//AudioManager_.LoadSong("asset/sounds/StartCutScene.mp3");
	//AudioManager_.PlaySong("asset/sounds/StartCutScene.mp3");
	//start = new Object();
	//start->SetTranslation({ 0, 0 });
	//start->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	//start->SetDepth(-0.6f);
	//start->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	//start->SetObjectType(ObjectType::Background);
	//start->AddComponent(new Sprite("asset/images/Page/Start1.png"));

	//start1 = new Object();
	//start1->SetTranslation({ 0, 0 });
	//start1->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	//start1->SetDepth(-0.6f);
	//start1->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	//start1->SetObjectType(ObjectType::Background);
	//start1->AddInitComponent(new Animation("asset/images/Page/StartCutScene.png", "cut", 20, 0.1f, false));
	//start1->GetComponentByTemplate<Animation>()->SetIsActive(false);

	//Objectmanager_.AddObject(start);
	//Objectmanager_.AddObject(start1);
}

void StartCutScene::Update(float dt)
{
    if (Input::IsKeyTriggered(GLFW_KEY_KP_0))
        test = { 1000,1000 };
    if (Input::IsKeyTriggered(GLFW_KEY_KP_1))
        test = { 0,0 };
    if (Input::IsKeyTriggered(GLFW_KEY_KP_2))
        test = { 300,300 };
    if (Input::IsKeyTriggered(GLFW_KEY_KP_3))
        test = { -300,-300 };

    if(button_.IntersectionCheck(Input::GetMousePos()))
    {
		if (Input::IsMouseTriggered(GLFW_MOUSE_BUTTON_LEFT)) 
		{
			if (button_.GetSelect().first == check && button_.GetSelect().second != CollisionState::WasCollided)
			{
				std::cout << "Action " << std::endl;
				button_.GetSelect().second = CollisionState::WasCollided;
			}
			if (button_.GetSelect().first == check1 && button_.GetSelect().second != CollisionState::WasCollided)
			{
				std::cout << "Action 하라이기" << std::endl;
				button_.GetSelect().second = CollisionState::WasCollided;
			}
		}
    }
	//timer += dt;

	//if (!is_end_start_sprite)
	//{
	//	if (timer >= 3.0f)
	//	{
	//		start->GetComponentByTemplate<Sprite>()->ChangeSprite("asset/images/Page/Start2.png");
	//		is_end_start_sprite = true;
	//	}
	//}
	//else
	//{
	//	if(!is_start_animation)
	//	{
	//		if (timer >= 6.0f)
	//		{
	//			start->SetInvisible();
	//			start1->GetComponentByTemplate<Animation>()->SetIsActive(true);
	//			is_start_animation = true;
	//		}
	//	}
	//}

	//if(is_start_animation)
	//{
	//	if(start1->GetComponentByTemplate<Animation>()->IsDone())
	//	{
	//		SetLevelIndicator("Level1");
	//		ChangeLevel("Level1");
	//	}
	//}

 //   if(Input::IsKeyAnyTriggered())
 //   {
 //       SetLevelIndicator("Level1");
 //       ChangeLevel("Level1");
 //   }
}

void StartCutScene::ShutDown()
{
	UnLoad();
}
