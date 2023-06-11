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
	, m_pAnimator{ nullptr }
{

}

void pacman::Pacman::Loaded()
{
	Character::Loaded();

	SetupAnimations();

	AddState(State::Walking,
		{},
		std::bind(&Pacman::UpdateWalking, this),
		{});

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

void pacman::Pacman::SetupAnimations()
{
	m_pAnimator = GetGameObject()->GetComponent<dae::Animator>();

	const float animSpeed{ 0.1f };

	m_pAnimator->AddAnimation(AnimId::WalkX, 3, { 0,0 }, 16, 16, animSpeed, true, SDL_FLIP_HORIZONTAL);
	m_pAnimator->AddAnimation(AnimId::WalkY, 3, { 0,16 }, 16, 16, animSpeed, true, SDL_FLIP_VERTICAL);
	m_pAnimator->AddAnimation(AnimId::Die, 15, { 0,32 }, 16, 16, animSpeed, false);
}

void pacman::Pacman::Start()
{
	Reset();
	m_pAnimator->SetDst({ 0, 0, 16, 16 });
}

void pacman::Pacman::UpdateWalking()
{
	m_pAgent->MoveDirection(m_Direction);
	const glm::ivec2 newPos{ m_pAgent->GetGridPosition() };
	GetGameObject()->SetLocalPosition(newPos.x, newPos.y);

	handlePickups();
	HandleWalkingAnim();

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

void pacman::Pacman::HandleWalkingAnim()
{
	const glm::ivec2 dir{ m_pAgent->GetDirection() };

	if(dir.y == 0)
	{
		if (dir.x > 0)
			m_pAnimator->Mirror(true);
		else
			m_pAnimator->Mirror(false);

		m_pAnimator->SetAnimation(AnimId::WalkX);
	}
	else
	{
		if (dir.y > 0)
			m_pAnimator->Mirror(true);
		else
			m_pAnimator->Mirror(false);

		m_pAnimator->SetAnimation(AnimId::WalkY);
	}
}

void pacman::Pacman::EnterDead()
{
	m_pAnimator->SetAnimation(AnimId::Die);

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
