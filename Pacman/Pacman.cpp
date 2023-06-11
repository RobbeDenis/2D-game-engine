#include "Pacman.h"
#include <iostream>
#include "PacmanEvents.h"
#include <GameObject.h>
#include <ETime.h>
#include "Ghost.h"

pacman::Pacman::Pacman(dae::GameObject* pGameObject)
	: Character(pGameObject)
	, m_pCollider{ nullptr }
	, m_MaxDeathTime{ 2 }
	, m_DeathTime{ }
	, m_Lives{ 3 }
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
		std::bind(&Pacman::ExitDead, this));

	AddState(State::Disabled, {}, {}, {});

	SetState(State::Walking);

	m_pCollider = GetGameObject()->GetComponent<dae::Collider>();
	if (m_pCollider == nullptr)
		throw std::runtime_error("Collider was not found");

	m_pCollider->SetDimensions(12, 12);
	m_pCollider->SetOffset(2, 2);

	m_pAgent->SetMovementSpeed(150.f);
}

void pacman::Pacman::UpdateWalking()
{
	m_pAgent->MoveDirection(m_Direction);
	const glm::ivec2 newPos{ m_pAgent->GetGridPosition() };
	GetGameObject()->SetLocalPosition(newPos.x, newPos.y);

	handlePickups();

	const auto& colliders{ m_pCollider->GetColliders() };

	for (dae::Collider* const c : colliders)
	{
		if (c == m_pCollider)
			continue;

		if (c->GetTag() == "ghost" && m_pCollider->IsOverlappingWith(c))
		{
			Ghost* ghost = c->GetGameObject()->GetComponent<pacman::Ghost>();

			if (ghost->CanDie())
			{
				ghost->Kill();
				Notify(PEvents::GhostKilled);
			}
			else if (ghost->CanKill())
			{
				Kill();
			}
		}
	}
}

void pacman::Pacman::ExitWalking()
{
	std::cout << "Exit Walking\n";
}

void pacman::Pacman::EnterDead()
{
	Notify(PEvents::PacmanDied);
	--m_Lives;
}

void pacman::Pacman::UpdateDead()
{
	const float elapsed{ dae::ETime::GetInstance().GetDeltaTime() };
	m_DeathTime += elapsed;

	if (m_DeathTime >= m_MaxDeathTime)
	{
		if (m_Lives < 0)
			SetState(State::Disabled);
		else
			SetState(State::Walking);
	}
}

void pacman::Pacman::ExitDead()
{
	m_DeathTime = 0.f;
	m_Direction = { 0,0 }; 
	m_pAgent->Reset(m_SpawnPoint);
}

void pacman::Pacman::handlePickups()
{
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
		break;
	default:
		break;
	}
}

void pacman::Pacman::Start()
{
	Reset();
}

void pacman::Pacman::Reset()
{
	SetState(State::Walking);
	m_pAgent->Reset(m_SpawnPoint);
	m_Direction = { 0,0 };
	m_Lives = 3;

	switch (m_pAgent->Pickup())
	{
	case CellType::Dot:
		Notify(PEvents::PlayerStart);
		break;
	}
}

void pacman::Pacman::Kill()
{
	SetState(State::Dead);
}
