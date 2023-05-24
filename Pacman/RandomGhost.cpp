#include "RandomGhost.h"
#include "GridAgent.h"
#include <GameObject.h>
#include <random>

pacman::RandomGhost::RandomGhost(dae::GameObject* pGameObject)
	: Character(pGameObject)
	, m_PrevCoordinate{ }
{
}

void pacman::RandomGhost::Loaded()
{
	Character::Loaded();

	AddState(State::Start,
		std::bind(&RandomGhost::EnterStart, this),
		std::bind(&RandomGhost::UpdateStart, this),
		{});

	AddState(State::Wander,
		{}, 
		std::bind(&RandomGhost::UpdateWander, this),
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
		throw std::runtime_error("Ghost started at wrong posiiton");
	}
}

void pacman::RandomGhost::UpdateStart()
{
	SetState(State::Wander);
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