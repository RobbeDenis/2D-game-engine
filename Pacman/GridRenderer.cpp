#include "GridRenderer.h"
#include <GameObject.h>
#include <Renderer.h>
#include <ResourceManager.h>
#include <SDL.h>
#include "Grid.h"

pacman::GridRenderer::GridRenderer(dae::GameObject* pGameObject)
	: dae::RenderComponent(pGameObject)
	, m_pGrid{ nullptr }
	, m_pMask{ nullptr }
	, m_DebugGridEnabled{ false }
	, m_pTarget{ nullptr }
	, m_Width{ 0 }
	, m_Height{ 0 }
{

}

pacman::GridRenderer::~GridRenderer()
{
	SDL_DestroyTexture(m_pMask);
	SDL_DestroyTexture(m_pTarget);
}

void pacman::GridRenderer::Start()
{
	if (m_pGrid == nullptr)
		return;

	m_Width = static_cast<int>(m_pGrid->GetCellSize() * m_pGrid->GetColums());
	m_Height = static_cast<int>(m_pGrid->GetCellSize() * m_pGrid->GetRows());

	m_pTarget = SDL_CreateTexture(dae::Renderer::GetInstance().GetSDLRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_Width, m_Height);
	m_pMask = SDL_CreateTexture(dae::Renderer::GetInstance().GetSDLRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, m_Width, m_Height);

	UpdateMask();
}

void pacman::GridRenderer::Render() const
{
	const auto& pos = GetGameObject()->GetWorldPosition();
	auto& renderer = dae::Renderer::GetInstance();

	renderer.RenderMaskedTexture(*m_pTexture, m_pMask, m_pTarget, pos.x, pos.y, m_Width, m_Height);

	if (m_pGrid == nullptr || !m_DebugGridEnabled)
		return;

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

void pacman::GridRenderer::UpdateMask()
{
	if (m_pGrid == nullptr)
		throw std::runtime_error("m_pGrid is nullptr");


	const int colums{ static_cast<int>(m_pGrid->GetColums()) };
	const int rows{ static_cast<int>(m_pGrid->GetRows()) };

	unsigned char* pixels;
	int pitch;

	SDL_LockTexture(m_pMask, NULL, (void**)&pixels, &pitch);

	for (int x = 0; x < rows; ++x)
	{
		for (int y = 0; y < colums; ++y)
		{
			const unsigned char value = (m_pGrid->GetCellData(x, y) == CellType::Wall) * 255;
			FillCell(pixels, pitch, x, y, value);
		}
	}

	SDL_UnlockTexture(m_pMask);
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

void pacman::GridRenderer::SetTexture(std::shared_ptr<dae::Texture2D> texture)
{
	m_pTexture = texture;
}

void pacman::GridRenderer::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void pacman::GridRenderer::EnableDebugGrid(bool enable)
{
	m_DebugGridEnabled = enable;
}