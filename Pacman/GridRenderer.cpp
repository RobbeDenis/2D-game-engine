#include "GridRenderer.h"
#include <stdexcept>
#include <GameObject.h>
#include <Renderer.h>
#include "Grid.h"

pacman::GridRenderer::GridRenderer(dae::GameObject* pGameObject)
	: dae::RenderComponent(pGameObject)
	, m_pGrid{ nullptr }
{
}

void pacman::GridRenderer::Render() const
{
	if (m_pGrid == nullptr)
		return;

	auto& renderer = dae::Renderer::GetInstance();
	const glm::vec3 pos{ GetGameObject()->GetWorldPosition() };
	const int colums{ static_cast<int>(m_pGrid->GetColums()) };
	const int rows{ static_cast<int>(m_pGrid->GetRows()) };
	const int cellSize{ static_cast<int>(m_pGrid->GetCellSize()) };
	const int gridWidth{ static_cast<int>(colums * cellSize) };
	const int gridHeight{ static_cast<int>(rows * cellSize) };

	for (int c{ 0 }; c <= colums; ++c)
	{
		const int x{ static_cast<int>(pos.x) + c * cellSize };
		renderer.RenderLine(x, static_cast<int>(pos.y), x, static_cast<int>(pos.y) + gridHeight);
	}

	for (int r{ 0 }; r <= rows; ++r)
	{
		const int y{ static_cast<int>(pos.y) + r * cellSize };
		renderer.RenderLine(static_cast<int>(pos.x), y, static_cast<int>(pos.x) + gridWidth, y);
	}
}

void pacman::GridRenderer::SetGrid(Grid* pGrid)
{
	if (pGrid == nullptr)
		throw std::runtime_error("pGrid is nullptr");
	m_pGrid = pGrid;
}
