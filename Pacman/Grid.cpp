#include "Grid.h"
#include "GridRenderer.h"
#include <GameObject.h>
#include <fstream>
#include <ResourceManager.h>
#include "GridAgent.h"
#include <ETime.h>

pacman::Grid::Grid(dae::GameObject* pGameObject)
	: dae::Component(pGameObject)
	, m_Colums{ 0 }
	, m_Rows{ 0 }
	, m_CellSize{ 0 }
	, m_Cells{ }
{
}

void pacman::Grid::LoadFromFile(unsigned colums, unsigned rows, unsigned cellSize, const std::string& filename)
{
	m_Colums = colums;
	m_Rows = rows;
	m_CellSize = cellSize;

	const std::string filePath{ dae::ResourceManager::GetInstance().GetDataPath() + filename };

	std::ifstream file{ filePath };
	if (!file.is_open())
		throw std::runtime_error{ filename + " was not abled to be opened" };

	for (unsigned r{ 0 }; r < m_Rows; ++r)
	{
		std::string line;
		if (std::getline(file, line))
		{
			m_Cells.push_back({});
			for (unsigned c{ 0 }; c < m_Colums; ++c)
			{
				m_Cells[r].push_back(static_cast<int>(line[c]) - 48);
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

	Coordinate target{ coordinate.x + newDirection.x, coordinate.y + newDirection.y };

	if (m_Cells[target.x][target.y] == CellType::Wall)
	{
		glm::ivec2 newPos{ pos + newDirection * static_cast<int>(speed * elapsed) };
		const glm::ivec2 maxPos{ CalculateCellPosition(coordinate) };

		if (newDirection.x < 0 && newPos.x < maxPos.x)
			newPos.x = maxPos.x;
		if (newDirection.x > 0 && newPos.x > maxPos.x)
			newPos.x = maxPos.x;

		pAgent->SetGridPosition(newPos);

		pAgent->SetCoordinate(GetCoordinateFromPosition(pAgent->GetGridPosition()));

		//newPos.x = std::min(maxPos.x, std::max(std::min(newDirection.x, 1) * newPos.x, maxPos.x));

		return;
	}

	const glm::ivec2 newPos{ pos + newDirection * static_cast<int>(speed * elapsed) };
	pAgent->SetGridPosition(newPos);

	pAgent->SetCoordinate(GetCoordinateFromPosition(pAgent->GetGridPosition()));
}

pacman::Coordinate pacman::Grid::GetCoordinateFromPosition(const glm::ivec2& position)
{
	const glm::ivec2 gridPos{ static_cast<int>(GetGameObject()->GetWorldPosition().x), static_cast<int>(GetGameObject()->GetWorldPosition().y) };
	const glm::ivec2 gridSpace{ position - gridPos };
	//const Coordinate c{ (gridSpace.x + (m_CellSize / 2)) / m_CellSize, (gridSpace.y + (m_CellSize / 2)) / m_CellSize };
	const Coordinate c{ (gridSpace.x ) / m_CellSize, (gridSpace.y ) / m_CellSize };
	return c;
}

glm::ivec2 pacman::Grid::CalculateCellPosition(const Coordinate& coordinate)
{
	const glm::vec3 gridPos{ GetGameObject()->GetWorldPosition() };
	return { gridPos.x + coordinate.x * m_CellSize, gridPos.y + coordinate.y * m_CellSize };
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
