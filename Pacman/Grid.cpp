#include "Grid.h"
#include "GridRenderer.h"
#include <GameObject.h>
#include <fstream>
#include <ResourceManager.h>
#include "GridAgent.h"
#include <ETime.h>
#include "PacmanEvents.h"

pacman::Grid::Grid(dae::GameObject* pGameObject)
	: dae::Component(pGameObject)
	, m_Colums{ 27 }
	, m_Rows{ 29 }
	, m_CellSize{ 16 }
	, m_Cells{ }
	, m_Offset{ 1 }
{
	for (unsigned r{ 0 }; r < m_Rows; ++r)
	{
		m_Cells.push_back({});
		for (unsigned c{ 0 }; c < m_Colums; ++c)
		{
			m_Cells[r].push_back(Empty);
		}
	}
}

void pacman::Grid::LoadFromFile(const std::string& filename)
{
	const std::string filePath{ dae::ResourceManager::GetInstance().GetDataPath() + filename };

	std::ifstream file{ filePath };
	if (!file.is_open())
		throw std::runtime_error{ filename + " was not abled to be opened" };

	for (unsigned r{ 0 }; r < m_Rows; ++r)
	{
		std::string line;
		if (std::getline(file, line))
		{
			for (unsigned c{ 0 }; c < m_Colums; ++c)
			{
				m_Cells[r][c] = static_cast<int>(line[c]) - '0';
			}
		}
	}

	file.close();
}

void pacman::Grid::Loaded()
{
	GridRenderer* gridRenderer{ GetGameObject()->GetComponent<GridRenderer>() };

	if (gridRenderer == nullptr)
		throw std::runtime_error{ "GridRenderer was not found" };

	gridRenderer->SetGrid(this);
}

pacman::GridAgent* pacman::Grid::CreateAgent(const Coordinate& coordinate)
{
	std::unique_ptr<GridAgent> agent = std::make_unique<GridAgent>(this);
	GridAgent* raw = agent.get();
	raw->SetCoordinate(coordinate);
	raw->SetGridPosition(CalculateCellPosition(coordinate));
	m_pAgents.push_back(std::move(agent));	
	return raw;
}

void pacman::Grid::MoveAgentInDirection(GridAgent* pAgent, float speed, const glm::ivec2& newDirection)
{
	const float elapsed{ dae::ETime::GetInstance().GetDeltaTime() };
	const glm::ivec2 prevDirection{ pAgent->GetDirection() };
	const glm::ivec2 pos{ pAgent->GetGridPosition() };
	const Coordinate coordinate{ pAgent->GetCoordinate() };
	const glm::ivec2 gridPos{ static_cast<int>(GetGameObject()->GetWorldPosition().x), static_cast<int>(GetGameObject()->GetWorldPosition().y) };

	Coordinate target{ coordinate.x + newDirection.x, coordinate.y + newDirection.y };

	if (m_Cells[target.y][target.x] == CellType::Wall)
	{
		target = { coordinate.x + prevDirection.x, coordinate.y + prevDirection.y };
		glm::ivec2 newPos{ pos + prevDirection * static_cast<int>(speed * elapsed) };

		if (m_Cells[target.y][target.x] != CellType::Wall)
		{
			pAgent->SetGridPosition(newPos);
			pAgent->SetCoordinate(GetCoordinateFromPosition(pAgent->GetGridPosition()));
			return;
		}

		if (prevDirection == newDirection)
		{
			const glm::ivec2 maxPos{ CalculateCellPosition(coordinate) };

			if (newDirection.x < 0 && newPos.x < maxPos.x)
				newPos.x = maxPos.x;
			if (newDirection.x > 0 && newPos.x > maxPos.x)
				newPos.x = maxPos.x;

			if (newDirection.y < 0 && newPos.y < maxPos.y)
				newPos.y = maxPos.y;
			if (newDirection.y > 0 && newPos.y > maxPos.y)
				newPos.y = maxPos.y;

			pAgent->SetGridPosition(newPos);
			pAgent->SetCoordinate(GetCoordinateFromPosition(pAgent->GetGridPosition()));
		}

		return;
	}

	if (CanTurn(pos - gridPos, prevDirection + newDirection))
	{
		const glm::ivec2 newPos{ pos + newDirection * static_cast<int>(speed * elapsed) };
		pAgent->SetGridPosition(newPos);
		pAgent->SetCoordinate(GetCoordinateFromPosition(pAgent->GetGridPosition()));
		pAgent->SetDirection(newDirection);
	}
	else
	{
		const glm::ivec2 newPos{ pos + prevDirection * static_cast<int>(speed * elapsed) };
		pAgent->SetGridPosition(newPos);
		pAgent->SetCoordinate(GetCoordinateFromPosition(pAgent->GetGridPosition()));
	}
}

pacman::Coordinate pacman::Grid::GetCoordinateFromPosition(const glm::ivec2& position)
{
	const glm::ivec2 gridPos{ static_cast<int>(GetGameObject()->GetWorldPosition().x), static_cast<int>(GetGameObject()->GetWorldPosition().y) };
	const glm::ivec2 gridSpace{ position - gridPos };
	const Coordinate c{ (gridSpace.x + (m_CellSize / 2)) / m_CellSize, (gridSpace.y + (m_CellSize / 2)) / m_CellSize };
	return c;
}

glm::ivec2 pacman::Grid::CalculateCellPosition(const Coordinate& coordinate)
{
	const glm::vec3 gridPos{ GetGameObject()->GetWorldPosition() };
	return { gridPos.x + coordinate.x * m_CellSize, gridPos.y + coordinate.y * m_CellSize };
}

bool pacman::Grid::CanTurn(const glm::ivec2& pos, const glm::ivec2& sumDir)
{
	return (sumDir.x == 0 && sumDir.y == 0) || (pos.x % m_CellSize <= m_Offset) && (pos.y % m_CellSize <= m_Offset);
}

void pacman::Grid::PrintGrid() const
{
	for (unsigned r{ 0 }; r < m_Rows; ++r)
	{
		for (unsigned c{ 0 }; c < m_Colums; ++c)
			std::cout << m_Cells[r][c] << " ";
		std::cout << "\n";
	}
}

unsigned pacman::Grid::Pickup(const Coordinate& c)
{
	const Coordinate safeC{ std::clamp(c.x, 0U, m_Rows), std::clamp(c.y, 0U, m_Colums) };

	unsigned type{ m_Cells[safeC.y][safeC.x] };

	if (type == CellType::Empty || type == CellType::Wall)
		return type;

	m_Cells[safeC.y][safeC.x] = CellType::Empty;
	Notify(PEvents::GridItemsChanged);

	if (CheckForWinCondition())
		Notify(PEvents::AllItemsCollected);

	return type;
}

bool pacman::Grid::CheckForWinCondition() const
{
	for (auto& col : m_Cells)
	{
		for (unsigned type : col)
		{
			if (type > Wall)
				return false;
		}
	}
	return true;
}

unsigned pacman::Grid::GetCellData(unsigned r, unsigned c) const 
{ 
	const Coordinate safeC{ std::clamp(r, 0U, m_Rows - 1), std::clamp(c, 0U, m_Colums - 1) };
	return m_Cells[safeC.x][safeC.y];
}