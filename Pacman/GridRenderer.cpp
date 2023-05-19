#include "GridRenderer.h"
#include <GameObject.h>
#include <Renderer.h>
#include <ResourceManager.h>
#include <SDL.h>
#include "Grid.h"
#include "GridAgent.h"

pacman::GridRenderer::GridRenderer(dae::GameObject* pGameObject)
	: dae::RenderComponent(pGameObject)
	, m_pGrid{ nullptr }
	, m_pWallMask{ nullptr }
	, m_DebugGridEnabled{ false }
	, m_pWallTarget{ nullptr }
	, m_Width{ 0 }
	, m_Height{ 0 }
	, m_DebugAgentsEnabled{ false }
	, m_pDotMask{ nullptr }
	, m_pDotTarget{ nullptr }
	, m_pPowerTexture{ nullptr }
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture("BlankLevel.png");
	m_pPowerTexture = dae::ResourceManager::GetInstance().LoadTexture("power.png");
	m_pDotTexture = dae::ResourceManager::GetInstance().LoadTexture("dots.png");
	m_pCherryTexture = dae::ResourceManager::GetInstance().LoadTexture("cherry.png");
	m_pStrawberryTexture = dae::ResourceManager::GetInstance().LoadTexture("strawberry.png");
	m_pMelonTexture = dae::ResourceManager::GetInstance().LoadTexture("melon.png");
}

pacman::GridRenderer::~GridRenderer()
{
	SDL_DestroyTexture(m_pWallMask);
	SDL_DestroyTexture(m_pWallTarget);
	SDL_DestroyTexture(m_pDotMask);
	SDL_DestroyTexture(m_pDotTarget);
}

void pacman::GridRenderer::Start()
{
	if (m_pGrid == nullptr)
		return;

	m_Width = static_cast<int>(m_pGrid->GetCellSize() * m_pGrid->GetColums());
	m_Height = static_cast<int>(m_pGrid->GetCellSize() * m_pGrid->GetRows());

	m_pWallTarget = SDL_CreateTexture(dae::Renderer::GetInstance().GetSDLRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_Width, m_Height);
	m_pWallMask = SDL_CreateTexture(dae::Renderer::GetInstance().GetSDLRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, m_Width, m_Height);

	m_pDotTarget = SDL_CreateTexture(dae::Renderer::GetInstance().GetSDLRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_Width, m_Height);
	m_pDotMask = SDL_CreateTexture(dae::Renderer::GetInstance().GetSDLRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, m_Width, m_Height);

	UpdateMask(m_pWallMask, CellType::Wall);
	UpdateMask(m_pDotMask, CellType::Dot);
}

void pacman::GridRenderer::Render() const
{
	const auto& pos = GetGameObject()->GetWorldPosition();
	auto& renderer = dae::Renderer::GetInstance();

	renderer.RenderMaskedTexture(*m_pTexture, m_pWallMask, m_pWallTarget, pos.x, pos.y, m_Width, m_Height);
	renderer.RenderMaskedTexture(*m_pDotTexture, m_pDotMask, m_pDotTarget, pos.x, pos.y, m_Width, m_Height);
	RenderItems();


	if (m_pGrid == nullptr)
		return;

	if (m_DebugGridEnabled)
	{
		const int colums{ static_cast<int>(m_pGrid->GetColums()) };
		const int rows{ static_cast<int>(m_pGrid->GetRows()) };
		const int cellSize{ static_cast<int>(m_pGrid->GetCellSize()) };

		for (int c{ 0 }; c <= colums; ++c)
		{
			const int x{ static_cast<int>(pos.x) + c * cellSize };
			renderer.RenderLine(x, static_cast<int>(pos.y), x, static_cast<int>(pos.y) + m_Height);
		}

		for (int r{ 0 }; r <= rows; ++r)
		{
			const int y{ static_cast<int>(pos.y) + r * cellSize };
			renderer.RenderLine(static_cast<int>(pos.x), y, static_cast<int>(pos.x) + m_Width, y);
		}
	}

	if (m_DebugAgentsEnabled)
	{
		auto& agents{ m_pGrid->GetAgents() };
		const int cellSize{ static_cast<int>(m_pGrid->GetCellSize()) };

		for (const auto& agent : agents)
		{
			const Coordinate c{ agent->GetCoordinate() };
			const int x{ static_cast<int>(pos.x) + cellSize * static_cast<int>(c.x) };
			const int y{ static_cast<int>(pos.y) + cellSize * static_cast<int>(c.y) };

			SDL_Color color{ 255,0,0 };

			renderer.RenderLine(x, y, x + cellSize, y, color);
			renderer.RenderLine(x, y, x , y + cellSize, color);
			renderer.RenderLine(x + cellSize, y, x + cellSize, y + cellSize, color);
			renderer.RenderLine(x, y + cellSize, x + cellSize, y + cellSize, color);
		}
	}
}

void pacman::GridRenderer::RenderItems() const
{
	auto& renderer = dae::Renderer::GetInstance();
	const unsigned colums{ m_pGrid->GetColums() };
	const unsigned rows{ m_pGrid->GetRows() };

	for (unsigned c{ 0 }; c < colums; ++c)
	{
		for (unsigned r{ 0 }; r < rows; ++r)
		{
			switch (m_pGrid->GetCellData(r, c))
			{	
				case CellType::Power:
				{
					const glm::ivec2 pos{ m_pGrid->CalculateCellPosition({c, r}) };
					renderer.RenderTexture(*m_pPowerTexture, static_cast<float>(pos.x), static_cast<float>(pos.y));
					break;
				}
				case CellType::Cherry:
				{
					const glm::ivec2 pos{ m_pGrid->CalculateCellPosition({c, r}) };
					renderer.RenderTexture(*m_pCherryTexture, static_cast<float>(pos.x), static_cast<float>(pos.y));
					break;
				}
				case CellType::Strawberry:
				{
					const glm::ivec2 pos{ m_pGrid->CalculateCellPosition({c, r}) };
					renderer.RenderTexture(*m_pStrawberryTexture, static_cast<float>(pos.x), static_cast<float>(pos.y));
					break;
				}
				case CellType::Melon:
				{
					const glm::ivec2 pos{ m_pGrid->CalculateCellPosition({c, r}) };
					renderer.RenderTexture(*m_pMelonTexture, static_cast<float>(pos.x), static_cast<float>(pos.y));
					break;
				}
				default:
					break;
			}
		}
	}
}

void pacman::GridRenderer::UpdateMask(SDL_Texture* pMask, unsigned type)
{
	if (m_pGrid == nullptr)
		throw std::runtime_error("m_pGrid is nullptr");


	const int colums{ static_cast<int>(m_pGrid->GetColums()) };
	const int rows{ static_cast<int>(m_pGrid->GetRows()) };

	unsigned char* pixels;
	int pitch;

	SDL_LockTexture(pMask, NULL, (void**)&pixels, &pitch);

	for (int x = 0; x < rows; ++x)
	{
		for (int y = 0; y < colums; ++y)
		{
			const int full = 255;
			const unsigned char value = (m_pGrid->GetCellData(x, y) == type) * full;
			FillCell(pixels, pitch, x, y, value);
		}
	}

	SDL_UnlockTexture(pMask);
}

void pacman::GridRenderer::FillCell(unsigned char* pixels, int pitch, int gridX, int gridY, unsigned char value)
{
	const int cellSize{ static_cast<int>(m_pGrid->GetCellSize()) };

	for (int y = gridX * cellSize; y < (gridX + 1) * cellSize; ++y)
	{
		for (int x = gridY * cellSize; x < (gridY + 1) * cellSize; ++x)
		{
			const int byteWidth = 4;
			const int index = y * pitch + x * byteWidth;
			pixels[index] = value;
			pixels[index + 1] = value;
			pixels[index + 2] = value;
			pixels[index + 3] = value;
		}
	}
}

void pacman::GridRenderer::SetGrid(Grid* pGrid)
{
	if (pGrid == nullptr)
		throw std::runtime_error("pGrid is nullptr");
	m_pGrid = pGrid;
}

void pacman::GridRenderer::EnableDebugGrid(bool enable)
{
	m_DebugGridEnabled = enable;
}

void pacman::GridRenderer::EnableDebugAgents(bool enable)
{
	m_DebugAgentsEnabled = enable;
}