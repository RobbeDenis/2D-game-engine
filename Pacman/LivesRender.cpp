#include "LivesRender.h"
#include <ResourceManager.h>
#include <GameObject.h>
#include <Renderer.h>

pacman::LivesRender::LivesRender(dae::GameObject* pGameObject)
	: RenderComponent(pGameObject)
	, m_pLives{ nullptr }
	, m_Spacing{ 4 }

{
}

void pacman::LivesRender::Render() const
{
	if (m_pLives == nullptr)
		return;

	const auto& pos = GetGameObject()->GetWorldPosition();
	const int lives{ m_pLives->GetLives() };
	const int offset{ m_pTexture->GetSize().x + m_Spacing };

	for (int i{}; i < lives; ++i)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x + (i * offset), pos.y);
	}
}

void pacman::LivesRender::SetLivesDisplay(LivesDisplay* pLives)
{
	m_pLives = pLives;
}

void pacman::LivesRender::SetTexture(std::shared_ptr<dae::Texture2D> texture)
{
	m_pTexture = texture;
}

void pacman::LivesRender::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}