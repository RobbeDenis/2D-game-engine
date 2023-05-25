#include "Ghost.h"
#include <GameObject.h>

pacman::Ghost::Ghost(dae::GameObject* pGameObject)
	: Character(pGameObject)
	, m_pCollider{ nullptr }
{
}

void pacman::Ghost::Loaded()
{
	Character::Loaded();

	m_pCollider = GetGameObject()->GetComponent<dae::Collider>();
	if (!m_pCollider)
		throw std::runtime_error("Collider was not found");

	m_pCollider->SetDimensions(12, 12);
	m_pCollider->SetOffset(2, 2);
	m_pCollider->SetTag("ghost");
}
