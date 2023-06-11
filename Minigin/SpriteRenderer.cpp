#include "SpriteRenderer.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::SpriteRenderer::SpriteRenderer(GameObject* pGameObject)
	: dae::RenderComponent(pGameObject)
	, m_UseSrc{ false }
	, m_Dst{ }
	, m_Src{ }
{

}

void dae::SpriteRenderer::Render() const
{
	if (!m_UseSrc)
	{
		RenderComponent::Render();
	}
	else
	{
		auto& renderer = Renderer::GetInstance();
		const auto& pos = GetGameObject()->GetWorldPosition();
		SDL_Rect dst{ static_cast<int>(pos.x) + m_Dst.x, static_cast<int>(pos.y) + m_Dst.y, m_Dst.w, m_Dst.h };
		renderer.RenderTexture(*m_pTexture, m_Src, dst, m_Flip);
	}
}

void dae::SpriteRenderer::SetTexture(std::shared_ptr<dae::Texture2D> texture)
{
	m_pTexture = texture;
}

void dae::SpriteRenderer::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::SpriteRenderer::SetSrc(const SDL_Rect& src)
{
	m_Src = src;
}

void dae::SpriteRenderer::SetDst(const SDL_Rect& dst)
{
	m_Dst = dst;
}

void dae::SpriteRenderer::UseSrc(bool use)
{
	m_UseSrc = use;
}

void dae::SpriteRenderer::SetFlip(SDL_RendererFlip flip)
{
	m_Flip = flip;
}
