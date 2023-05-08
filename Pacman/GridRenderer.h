#pragma once
#include <RenderComponent.h>

namespace pacman
{
	class Grid;
	class GridRenderer : public dae::RenderComponent
	{
	public:
		GridRenderer(dae::GameObject* pGameObject);

		void Render() const override;

		void SetGrid(Grid* pGrid);

	private:
		Grid* m_pGrid;
	};
}