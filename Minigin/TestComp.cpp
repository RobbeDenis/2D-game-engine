#include "TestComp.h"
#include "GameObject.h"

dae::TestComp::TestComp(GameObject* pGameObject)
	: dae::Component(pGameObject)
{

}

void dae::TestComp::Start()
{
	GameObject* go = GetGameObject();
	go->GetChild("left")->Destroy();
	go->GetChild(2)->GetChild("2 child")->Destroy();
	go->GetChild(3)->Destroy();
	GameObject* left = go->GetChild("left")->GetChild("left child");
	go->GetChild("left")->DetachChild(left);
	go->GetChild("2")->AttachChild(go->GetChild(3)->GetChild("3 child"), true);
}