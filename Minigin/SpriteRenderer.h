#pragma once
#include "RenderComponent.h"
#include <string>
#include <SDL.h>

namespace dae
{
	class SpriteRenderer final : public RenderComponent
	{
	public:
		SpriteRenderer(GameObject* pGameObject);

		void Render() const override;

		void SetTexture(std::shared_ptr<dae::Texture2D> texture);
		void SetTexture(const std::string& filename);
		void SetSrc(const SDL_Rect& src);
		void SetDst(const SDL_Rect& dst);
		void UseSrc(bool use);
		void SetFlip(SDL_RendererFlip flip);

	private:
		SDL_Rect m_Src;
		SDL_Rect m_Dst;
		SDL_RendererFlip  m_Flip;
		bool m_UseSrc;
	};
}