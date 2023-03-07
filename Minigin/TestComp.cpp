#include "TestComp.h"

dae::TestComp::TestComp(GameObject* pGameObject)
	: dae::Component(pGameObject)
{

}

void dae::TestComp::Start()
{
	auto go = GetGameObject();
	go->GetChild("left").lock()->Destroy();
	go->GetChild(2).lock()->GetChild("2 child").lock()->Destroy();
	go->GetChild(3).lock()->Destroy();
	auto left = go->GetChild("left").lock()->GetChild("left child");
	go->GetChild("left").lock()->DetachChild(left);
	go->GetChild("2").lock()->AttachChild(go->GetChild(3).lock()->GetChild("3 child"), true);
}