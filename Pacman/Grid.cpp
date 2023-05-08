#include "Grid.h"
#include "GridRenderer.h"
#include <GameObject.h>

pacman::Grid::Grid(dae::GameObject* pGameObject)
	: dae::Component(pGameObject)
	, m_Colums{ 5 }
	, m_Rows{ 5 }
	, m_CellSize{ 16 }
{
}

void pacman::Grid::Initialize(unsigned colums, unsigned rows, unsigned cellSize)
{
	m_Colums = colums;
	m_Rows = rows;
	m_CellSize = cellSize;
}

void pacman::Grid::Loaded()
{
	GridRenderer* gridRenderer{ GetGameObject()->GetComponent<GridRenderer>() };

	if (gridRenderer == nullptr)
		throw std::runtime_error{ "GridRenderer was not found" };

	gridRenderer->SetGrid(this);
}
