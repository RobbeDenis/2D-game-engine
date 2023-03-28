#pragma once
#include "RenderComponent.h"
#include <SDL_ttf.h>
#include <string>

namespace dae
{
	class Font;

	class TextRenderer final : public RenderComponent
	{
	public:
		TextRenderer(GameObject* pGameObject);

		void Update() override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);
		void SetFont(std::shared_ptr<Font> pFont);

	private:
		std::string m_Text;
		SDL_Color m_Color;
		std::shared_ptr<Font> m_pFont;
		bool m_Dirty;
	};
}
