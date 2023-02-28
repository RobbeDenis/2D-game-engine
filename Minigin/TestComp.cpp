#include "TestComp.h"

dae::TestComp::TestComp(dae::GameObject* pGameObject)
	: dae::Component(pGameObject)
{

}

void dae::TestComp::Start()
{
	Destroy();
}