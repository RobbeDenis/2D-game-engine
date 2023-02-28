#include "Component.h"

dae::Component::Component(GameObject* pGameObject)
	: m_pGameObject{ pGameObject }
	, m_IsMarkedForDestroy{ false }
{

}

dae::Component::~Component()
{
	OnDestroy();
}

void dae::Component::Destroy()
{
	m_IsMarkedForDestroy = true;
	m_pGameObject->SetDirtyComponentDestroy();
}

bool dae::Component::IsMarkedForDestroy() const
{
	return m_IsMarkedForDestroy;
}
