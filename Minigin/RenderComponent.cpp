#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"

dae::RenderComponent::RenderComponent(GameObject* pGameObject)
	: dae::Component(pGameObject)
{
	
}

dae::RenderComponent::~RenderComponent()
{
	GetGameObject()->GetScene()->RemoveRenderComponent(this);
}

void dae::RenderComponent::Loaded()
{
	GetGameObject()->GetScene()->AddRenderComponent(this);
}

void dae::RenderComponent::Render() const
{
	if (m_pTexture == nullptr)
		return;

	const auto& pos = GetGameObject()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}