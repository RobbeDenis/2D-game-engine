#pragma once
#include <RenderComponent.h>
#include <string>
#include "LivesDisplay.h"

namespace pacman
{
	class LivesRender :	public dae::RenderComponent
	{
	public:
		LivesRender(dae::GameObject* pGameObject);

		void Render() const override;
		void SetLivesDisplay(LivesDisplay* pLives);

		void SetTexture(std::shared_ptr<dae::Texture2D> texture);
		void SetTexture(const std::string& filename);

	private:
		LivesDisplay* m_pLives;
		int m_Spacing;
	};
}