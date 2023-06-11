#pragma once
#include <SDL.h>
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& src, const SDL_Rect& dst, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
		void RenderMaskedTexture(const Texture2D& texture, SDL_Texture* mask, SDL_Texture* target, float x, float y, int width, int height) const;
		void RenderLine(int x1, int y1, int x2, int y2, const SDL_Color& color = {0, 255, 0, 0}) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

	private:
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
	};
}

