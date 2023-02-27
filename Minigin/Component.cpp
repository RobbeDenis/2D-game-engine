#include "Component.h"

dae::Component::Component(GameObject* pGameObject)
	: m_pGameObject{ pGameObject }
	, m_MarkedForDestroy{ false }
{

}

void dae::Component::Destroy()
{
	m_MarkedForDestroy = true;
}
