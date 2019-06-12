#include "EndCutScene.hpp"

void EndCutScene::Initialize()
{
	end = new Object();
	end->SetTranslation({ 0, 0 });
	end->SetScale({ static_cast<float>(Application_.GetGLFWvidmode()->width), static_cast<float>(Application_.GetGLFWvidmode()->height) });
	end->SetDepth(-0.6f);
	end->SetMesh(mesh::CreateBox(1, { 255,255,255,255 }));
	end->SetObjectType(ObjectType::Background);
	end->AddInitComponent(new Animation("asset/images/Page/WinPage.png", "end",15, 0.1f, false));
}

void EndCutScene::Update(float dt)
{
	if(end->GetComponentByTemplate<Animation>()->IsDone())
		StateManager_.ToCredit();
}

void EndCutScene::ShutDown()
{
	UnLoad();
}
