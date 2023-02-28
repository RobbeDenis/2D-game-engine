#include "SpriteRenderer.h"
#include "ResourceManager.h"

dae::SpriteRenderer::SpriteRenderer(GameObject* pGameObject)
	: dae::RenderComponent(pGameObject)
{

}

void dae::SpriteRenderer::SetTexture(std::shared_ptr<dae::Texture2D> texture)
{
	m_pTexture = texture;
}

void dae::SpriteRenderer::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}