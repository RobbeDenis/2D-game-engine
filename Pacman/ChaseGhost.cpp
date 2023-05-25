#include "ChaseGhost.h"
#include <GameObject.h>
#include <random>

pacman::ChaseGhost::ChaseGhost(dae::GameObject* pGameObject)
	: Ghost(pGameObject)
	, m_PrevCoordinate{ }
	, m_pTarget{ nullptr }
	, m_ChaseAxis{ 0, 0 }
{

}

void pacman::ChaseGhost::Loaded()
{
	Ghost::Loaded();

	AddState(State::Start,
		{},
		std::bind(&ChaseGhost::UpdateStart, this),
		{});

	AddState(State::Chase,
		{},
		std::bind(&ChaseGhost::UpdateChase, this),
		{});

	AddState(State::Dead,
		{},
		std::bind(&ChaseGhost::UpdateDead, this),
		{});

	SetState(State::Start);
}

void pacman::ChaseGhost::UpdateStart()
{
	UpdateDirection();
	SetState(State::Chase);
}

void pacman::ChaseGhost::UpdateChase()
{
	UpdateDirection();

	m_pAgent->MoveDirection(m_Direction);
	const glm::ivec2 newPos{ m_pAgent->GetGridPosition() };
	GetGameObject()->SetLocalPosition(newPos.x, newPos.y);
}

void pacman::ChaseGhost::UpdateDead()
{
}

void pacman::ChaseGhost::UpdateDirection()
{
	if (!m_pTarget)
	{
		m_PrevCoordinate = m_pAgent->GetCoordinate();
		return;
	}

	if (m_PrevCoordinate != m_pAgent->GetCoordinate())
	{
		const Coordinate c{ m_pAgent->GetCoordinate() };
		const Coordinate ct{ m_pAgent->GetGrid()->GetCoordinateFromPosition(m_pTarget->GetLocalPosition()) };
		const glm::ivec2 toTarget{ glm::clamp(glm::ivec2{ ct.x - c.x, ct.y - c.y }, { -1, -1 }, { 1, 1 }) };

		const glm::ivec2 up{ 0, 1 };
		const glm::ivec2 down{ 0, -1 };
		const glm::ivec2 left{ -1, 0 };
		const glm::ivec2 right{ 1, 0 };
		const glm::ivec2 zero{ 0, 0 };

		std::vector<glm::ivec2> checkedDirections;

		if (m_pAgent->LookAt({ c.x + up.x, c.y + up.y }) != CellType::Wall)
		{
			if (m_Direction + up != zero)
				checkedDirections.push_back(up);
		}

		if (m_pAgent->LookAt({ c.x + down.x, c.y + down.y }) != CellType::Wall)
		{
			if (m_Direction + down != zero)
				checkedDirections.push_back(down);
		}

		if (m_pAgent->LookAt({ c.x + left.x, c.y + left.y }) != CellType::Wall)
		{
			if (m_Direction + left != zero)
				checkedDirections.push_back(left);
		}

		if (m_pAgent->LookAt({ c.x + right.x, c.y + right.y }) != CellType::Wall)
		{
			if (m_Direction + right != zero)
				checkedDirections.push_back(right);
		}

		for (const glm::ivec2& dir : checkedDirections)
		{
			if (dir.x != 0 && m_ChaseAxis.x != 0 && toTarget.x == dir.x)
			{
				m_Direction = dir;
				return;
			}
			else if (dir.y != 0 && m_ChaseAxis.y != 0 && toTarget.y == dir.y)
			{
				m_Direction = dir;
				return;
			}
		}

		if (!checkedDirections.empty())
		{
			int randomIndex = GetRandomInt(0, static_cast<unsigned>(checkedDirections.size() - 1));
			m_Direction = checkedDirections[randomIndex];
		}
	}

	m_PrevCoordinate = m_pAgent->GetCoordinate();
}

void pacman::ChaseGhost::SetTarget(dae::GameObject* pTarget)
{
	if (pTarget == nullptr)
		throw std::runtime_error("Target is nullptr");

	m_pTarget = pTarget;
}

void pacman::ChaseGhost::SetChaseAxis(int horizontal, int vertical)
{
	m_ChaseAxis.x = horizontal;
	m_ChaseAxis.y = -vertical;
}

unsigned pacman::ChaseGhost::GetRandomInt(unsigned min, unsigned max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution dis(min, max);
	return dis(gen);
}