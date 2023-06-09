#include "ChaseGhost.h"
#include <GameObject.h>
#include <random>
#include <ETime.h>

pacman::ChaseGhost::ChaseGhost(dae::GameObject* pGameObject)
	: Ghost(pGameObject)
	, m_PrevCoordinate{ }
	, m_pTarget{ nullptr }
	, m_ChaseAxis{ 0, 0 }
	, m_MaxRunTime{ 4 }
	, m_RunTime{ 0 }
	, m_MaxBlinkTime{ 2.f }
	, m_BlinkTime{ 0 }
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
		std::bind(&ChaseGhost::EnterChase, this),
		std::bind(&ChaseGhost::UpdateChase, this),
		{});
	
	AddState(State::Run,
		std::bind(&ChaseGhost::EnterRun, this),
		std::bind(&ChaseGhost::UpdateRun, this),
		{});

	AddState(State::Blink,
		std::bind(&ChaseGhost::EnterBlink, this),
		std::bind(&ChaseGhost::UpdateBlink, this),
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

void pacman::ChaseGhost::EnterChase()
{
	std::cout << "Chase\n";
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
		else
		{
			m_Direction = -m_Direction;
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

void pacman::ChaseGhost::SetChaseAxis(const glm::ivec2& axis)
{
	m_ChaseAxis.x = axis.x;
	m_ChaseAxis.y = -axis.y;
}

unsigned pacman::ChaseGhost::GetRandomInt(unsigned min, unsigned max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution dis(min, max);
	return dis(gen);
}

void pacman::ChaseGhost::Scare()
{
	SetState(State::Run);
}

void pacman::ChaseGhost::EnterRun()
{
	std::cout << "Running\n";
	m_Direction -= m_Direction;
	m_PrevCoordinate = { 0,0 };
	m_RunTime = 0;
}

void pacman::ChaseGhost::UpdateRun()
{
	const float elapsed{ dae::ETime::GetInstance().GetDeltaTime() };

	m_RunTime += elapsed;
	if (m_RunTime >= m_MaxRunTime)
	{
		SetState(State::Blink);
	}

	UpdateRunDirection();
	m_pAgent->MoveDirection(m_Direction);
	const glm::ivec2 newPos{ m_pAgent->GetGridPosition() };
	GetGameObject()->SetLocalPosition(newPos.x, newPos.y);
}

void pacman::ChaseGhost::EnterBlink()
{
	std::cout << "Blinking\n";
	m_BlinkTime = 0;
}

void pacman::ChaseGhost::UpdateBlink()
{
	const float elapsed{ dae::ETime::GetInstance().GetDeltaTime() };

	m_BlinkTime += elapsed;
	if (m_BlinkTime >= m_MaxBlinkTime)
	{
		m_PrevCoordinate = { 0,0 };
		UpdateDirection();
		SetState(State::Chase);
	}

	UpdateRunDirection();
	m_pAgent->MoveDirection(m_Direction);
	const glm::ivec2 newPos{ m_pAgent->GetGridPosition() };
	GetGameObject()->SetLocalPosition(newPos.x, newPos.y);
}

void pacman::ChaseGhost::UpdateRunDirection()
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
		const glm::ivec2 awayFromTarget{ glm::clamp(glm::ivec2{ c.x - ct.x, c.y - ct.y }, { -1, -1 }, { 1, 1 }) };

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
			if (awayFromTarget.x == dir.x)
			{
				m_Direction = dir;
				return;
			}
			else if (awayFromTarget.y == dir.y)
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
		else
		{
			m_Direction = -m_Direction;
		}
	}

	m_PrevCoordinate = m_pAgent->GetCoordinate();
}

void pacman::ChaseGhost::Kill()
{
	Reset();
}

bool pacman::ChaseGhost::CanKill() const
{
	return GetState() == State::Run || GetState() == State::Blink;
}

void pacman::ChaseGhost::Reset()
{
	SetState(State::Start);
	m_pAgent->Reset(m_SpawnPoint);
}