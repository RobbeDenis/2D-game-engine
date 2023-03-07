#include "TestComp.h"

dae::TestComp::TestComp(dae::GameObject* pGameObject)
	: dae::Component(pGameObject)
{

}

void dae::TestComp::Start()
{
	m_pGameObject->Destroy();
}