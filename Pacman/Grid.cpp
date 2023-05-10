#include "Grid.h"
#include "GridRenderer.h"
#include <GameObject.h>
#include <fstream>
#include <ResourceManager.h>

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

void pacman::Grid::PrintGrid() const
{
	for (unsigned r{ 0 }; r < m_Rows; ++r)
	{
		for (unsigned c{ 0 }; c < m_Colums; ++c)
			std::cout << m_Cells[r][c] << " ";
		std::cout << "\n";
	}
}
