#include "RenderComponent.h"
#include "Renderer.h"
#include "Scene.h"

dae::RenderComponent::RenderComponent(GameObject* pGameObject)
	: dae::Component(pGameObject)
{

}

void dae::RenderComponent::Loaded()
{
	m_pGameObject->GetScene()->AddRenderComponent(this);
}

void dae::RenderComponent::Render() const
{
	if (m_pTexture == nullptr)
		return;

	const auto& pos = m_pGameObject->GetTransform().GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}