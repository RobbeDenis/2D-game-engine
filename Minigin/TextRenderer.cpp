#include "TextRenderer.h"
#include "GameObject.h"
#include "Font.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::TextRenderer::TextRenderer(GameObject* pGameObject)
	: dae::RenderComponent(pGameObject)
	, m_Dirty{ false }
	, m_Color{ 255, 255, 255 }
	, m_Text{ " " }
{
	m_pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
}

void dae::TextRenderer::Update()
{
	dae::RenderComponent::Update();
	
	if (m_Dirty)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<Texture2D>(texture);
		m_Dirty = false;
	}
}

void dae::TextRenderer::SetText(const std::string& text)
{
	m_Text = text;
	m_Dirty = true;
}

void dae::TextRenderer::SetColor(const SDL_Color& color)
{
	m_Color = color;
	m_Dirty = true;
}

void dae::TextRenderer::SetFont(std::shared_ptr<Font> pFont)
{
	m_pFont = std::move(pFont);
	m_Dirty = true;
}
