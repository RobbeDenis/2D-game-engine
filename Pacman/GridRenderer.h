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
		void SetTexture(std::shared_ptr<dae::Texture2D> texture);
		void SetTexture(const std::string& filename);
		void EnableDebugGrid(bool enable);
		void EnableDebugAgents(bool enable);
		void UpdateMask();

	private:
		void FillCell(unsigned char* pixels,int pitch, int gridX, int gridY, unsigned char value);

		int m_Width;
		int m_Height;
		Grid* m_pGrid;
		SDL_Texture* m_pMask;
		SDL_Texture* m_pTarget;
		bool m_DebugGridEnabled;
		bool m_DebugAgentsEnabled;
	};
}