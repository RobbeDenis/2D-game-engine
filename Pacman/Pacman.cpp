#include "Pacman.h"
#include <iostream>
#include "PacmanEvents.h"
#include <GameObject.h>

pacman::Pacman::Pacman(dae::GameObject* pGameObject)
	: Character(pGameObject)
	, m_pCollider{ nullptr }
{

}

void pacman::Pacman::Loaded()
{
	Character::Loaded();

	AddState(State::Walking,
		{},
		std::bind(&Pacman::UpdateWalking, this),
		std::bind(&Pacman::ExitWalking, this));

	AddState(State::Dead,
		std::bind(&Pacman::EnterDead, this),
		std::bind(&Pacman::UpdateDead, this),
		{});

	SetState(State::Walking);

	m_pCollider = GetGameObject()->GetComponent<dae::Collider>();
	if (m_pCollider == nullptr)
		throw std::runtime_error("Collider was not found");

	m_pCollider->SetDimensions(16, 16);
}

void pacman::Pacman::UpdateWalking()
{
	m_pAgent->MoveDirection(m_Direction);
	const glm::ivec2 newPos{ m_pAgent->GetGridPosition() };
	GetGameObject()->SetLocalPosition(newPos.x, newPos.y);

	HandleCollisions();

	switch (m_pAgent->Pickup())
	{
	case CellType::Dot:
		Notify(PEvents::CDot);
		break;
	case CellType::Power:
		Notify(PEvents::CPower);
		break;
	case CellType::Cherry:
		Notify(PEvents::CFruit);
		break;
	case CellType::Strawberry:
		Notify(PEvents::CFruit);
		break;
	case CellType::Melon:
		Notify(PEvents::CFruit);
		SetState(State::Dead);
		break;
	default:
		break;
	}
}

void pacman::Pacman::EnterDead()
{
	std::cout << "Entered Dead\n";
}

void pacman::Pacman::ExitWalking()
{
	std::cout << "Exit Walking\n";
}

void pacman::Pacman::UpdateDead()
{
	
}

void pacman::Pacman::HandleCollisions()
{
	const auto& colliders{ m_pCollider->GetColliders() };

	for (const dae::Collider* c : colliders)
	{
		if (c == m_pCollider)
			continue;

		if (c->GetTag() == "ghost")
		{
			std::cout << "Ghost Hit\n";
		}
	}
}
