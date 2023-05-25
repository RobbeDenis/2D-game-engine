#include "Collider.h"
#include "GameObject.h"
#include "Scene.h"

dae::Collider::Collider(GameObject* pGameObject)
	: Component(pGameObject)
	, m_Rect{ }
	, m_Tag{ "none"}
{
}

void dae::Collider::Loaded()
{
	GetGameObject()->GetScene()->AddCollider(this);
}

bool dae::Collider::IsOverlappingWith(Collider* other)
{
	SDL_Rect otherRect = other->GetRect();

	return (m_Rect.x > otherRect.x + otherRect.w ||
		m_Rect.x + m_Rect.w < otherRect.x ||
		m_Rect.y > otherRect.y + otherRect.h ||
		m_Rect.y + m_Rect.h < otherRect.y);
}

const SDL_Rect& dae::Collider::GetRect() const
{
	return m_Rect;
}

void dae::Collider::SetDimensions(int x, int y, int w, int h)
{
	SetDimensions({ x, y, w, h });
}

void dae::Collider::SetDimensions(const SDL_Rect& rect)
{
	m_Rect = rect;
}

void dae::Collider::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

std::vector<dae::Collider*>& dae::Collider::GetColliders()
{
	return GetGameObject()->GetScene()->GetColliders();
}