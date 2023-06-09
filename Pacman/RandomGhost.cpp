#include "RandomGhost.h"
#include <GameObject.h>
#include <random>
#include <ETime.h>

pacman::RandomGhost::RandomGhost(dae::GameObject* pGameObject)
	: Ghost(pGameObject)
	, m_PrevCoordinate{ }
	, m_MaxRunTime{ 4 }
	, m_RunTime{ 0 }
	, m_MaxBlinkTime{ 2.f }
	, m_BlinkTime{ 0 }
{
}

void pacman::RandomGhost::Loaded()
{
	Ghost::Loaded();

	AddState(State::Start,
		std::bind(&RandomGhost::EnterStart, this),
		std::bind(&RandomGhost::UpdateStart, this),
		{});

	AddState(State::Wander,
		std::bind(&RandomGhost::EnterWander, this),
		std::bind(&RandomGhost::UpdateWander, this),
		{});

	AddState(State::Run,
		std::bind(&RandomGhost::EnterRun, this),
		std::bind(&RandomGhost::UpdateRun, this),
		std::bind(&RandomGhost::ExitRun, this));

	AddState(State::Blink,
		std::bind(&RandomGhost::EnterBlink, this),
		std::bind(&RandomGhost::UpdateBlink, this),
		{});

	AddState(State::Dead, 
		{}, 
		std::bind(&RandomGhost::UpdateDead, this), 
		{});

	SetState(State::Start);
}

void pacman::RandomGhost::EnterStart()
{
	const Coordinate c{ m_pAgent->GetCoordinate() };
	const Coordinate up{ c.x, c.y + 1 };
	const Coordinate down{ c.x, c.y - 1 };
	const Coordinate left{ c.x - 1, c.y };
	const Coordinate right{ c.x + 1, c.y };
	std::vector<Coordinate> checkedCoordinates;

	if (m_pAgent->LookAt(up) != CellType::Wall)
		checkedCoordinates.push_back(up);

	if (m_pAgent->LookAt(down) != CellType::Wall)
		checkedCoordinates.push_back(down);

	if (m_pAgent->LookAt(left) != CellType::Wall)
		checkedCoordinates.push_back(left);

	if (m_pAgent->LookAt(right) != CellType::Wall)
		checkedCoordinates.push_back(right);

	if (!checkedCoordinates.empty()) 
	{
		int randomIndex = GetRandomInt(0, static_cast<unsigned>(checkedCoordinates.size() - 1));
		Coordinate randomCoord = checkedCoordinates[randomIndex];
		m_Direction.x = randomCoord.x - c.x;
		m_Direction.y = randomCoord.y - c.y;
	}
	else 
	{
		throw std::runtime_error("Ghost started at wrong position");
	}
}

void pacman::RandomGhost::UpdateStart()
{
	SetState(State::Wander);
}

void pacman::RandomGhost::EnterWander()
{
	std::cout << "Wander\n";
}

void pacman::RandomGhost::UpdateWander()
{
	UpdateDirection();

	m_pAgent->MoveDirection(m_Direction);
	const glm::ivec2 newPos{ m_pAgent->GetGridPosition() };
	GetGameObject()->SetLocalPosition(newPos.x, newPos.y);

}

void pacman::RandomGhost::UpdateDead()
{

}

void pacman::RandomGhost::UpdateDirection()
{
	if (m_PrevCoordinate != m_pAgent->GetCoordinate())
	{
		const Coordinate c{ m_pAgent->GetCoordinate() };
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

unsigned pacman::RandomGhost::GetRandomInt(unsigned min, unsigned max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution dis(min, max);
	return dis(gen);
}

void pacman::RandomGhost::Reset()
{
	SetState(State::Start);
	m_pAgent->Reset(m_SpawnPoint);
}

void pacman::RandomGhost::Scare()
{
	SetState(State::Run);
}

void pacman::RandomGhost::EnterRun()
{
	std::cout << "Running\n";
	m_Direction = -m_Direction;
	m_RunTime = 0.f;
}

void pacman::RandomGhost::UpdateRun()
{
	const float elapsed{ dae::ETime::GetInstance().GetDeltaTime() };

	m_RunTime += elapsed;
	if (m_RunTime >= m_MaxRunTime)
	{
		SetState(State::Blink);
	}

	UpdateDirection();

	m_pAgent->MoveDirection(m_Direction);
	const glm::ivec2 newPos{ m_pAgent->GetGridPosition() };
	GetGameObject()->SetLocalPosition(newPos.x, newPos.y);
}

void pacman::RandomGhost::ExitRun()
{

}

void pacman::RandomGhost::EnterBlink()
{
	std::cout << "Blinking\n";
	m_BlinkTime = 0.f;
}

void pacman::RandomGhost::UpdateBlink()
{
	const float elapsed{ dae::ETime::GetInstance().GetDeltaTime() };

	m_BlinkTime += elapsed;
	if (m_BlinkTime >= m_MaxBlinkTime)
	{
		m_PrevCoordinate = { 0,0 };
		SetState(State::Start);
	}

	UpdateDirection();

	m_pAgent->MoveDirection(m_Direction);
	const glm::ivec2 newPos{ m_pAgent->GetGridPosition() };
	GetGameObject()->SetLocalPosition(newPos.x, newPos.y);
}

void pacman::RandomGhost::Kill()
{
	Reset();
}

bool pacman::RandomGhost::CanKill() const
{
	return GetState() == State::Run || GetState() == State::Blink;
}