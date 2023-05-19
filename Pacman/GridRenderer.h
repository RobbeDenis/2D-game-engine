#pragma once
#include <RenderComponent.h>
#include <string>

struct SDL_Texture;
namespace pacman
{
	class Grid;
	class GridRenderer : public dae::RenderComponent
	{
	public:
		GridRenderer(dae::GameObject* pGameObject);
		~GridRenderer();

		void Start() override;
		void Render() const override;

		void SetGrid(Grid* pGrid);
		void EnableDebugGrid(bool enable);
		void EnableDebugAgents(bool enable);

	private:
		void RenderItems() const;
		void UpdateMask(SDL_Texture* pMask, unsigned type);
		void FillCell(unsigned char* pixels,int pitch, int gridX, int gridY, unsigned char value);

		int m_Width;
		int m_Height;
		Grid* m_pGrid;
		std::shared_ptr<dae::Texture2D> m_pPowerTexture;
		std::shared_ptr<dae::Texture2D> m_pCherryTexture;
		std::shared_ptr<dae::Texture2D> m_pStrawberryTexture;
		std::shared_ptr<dae::Texture2D> m_pMelonTexture;
		std::shared_ptr<dae::Texture2D> m_pDotTexture;
		SDL_Texture* m_pDotMask;
		SDL_Texture* m_pDotTarget;
		SDL_Texture* m_pWallMask;
		SDL_Texture* m_pWallTarget;
		bool m_DebugGridEnabled;
		bool m_DebugAgentsEnabled;
	};
}