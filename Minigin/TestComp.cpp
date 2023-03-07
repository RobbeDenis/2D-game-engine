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
}