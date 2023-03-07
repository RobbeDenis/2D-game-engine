#include "Component.h"

dae::Component::Component(GameObject* pGameObject)
	: m_pGameObject{ pGameObject }
	, m_IsMarkedForDestroy{ false }
{

}

dae::Component::~Component()
{
	
}

dae::GameObject* dae::Component::GetGameObject() const
{
	return m_pGameObject;
}

void dae::Component::Destroy()
{
	m_IsMarkedForDestroy = true;
	m_pGameObject->SetComponentsMarkedForDestroy();
}

bool dae::Component::IsMarkedForDestroy() const
{
	return m_IsMarkedForDestroy;
}
