#include "Collider.h"
#include "GameObject.h"
#include "Scene.h"

dae::Collider::Collider(GameObject* pGameObject)
	: Component(pGameObject)
	, m_Rect{ }
	, m_Tag{ "none"}
	, m_Offset{ }
{
	
}

dae::Collider::~Collider()
{
	if(auto scene{ GetGameObject()->GetScene() })
		scene->RemoveCollider(this);
}

void dae::Collider::Loaded()
{
	GetGameObject()->GetScene()->AddCollider(this);
}

bool dae::Collider::IsOverlappingWith(Collider* other)
{
	SDL_Rect intersection;
	return SDL_IntersectRect(&GetRect(), &other->GetRect(), &intersection);

}

const SDL_Rect& dae::Collider::GetRect()
{
	m_Rect.x = static_cast<int>(GetGameObject()->GetWorldPosition().x) + m_Offset.x;
	m_Rect.y = static_cast<int>(GetGameObject()->GetWorldPosition().y) + m_Offset.y;
	return m_Rect;
}

void dae::Collider::SetDimensions(int w, int h)
{
	SetDimensions({ 0, 0, w, h });
}

void dae::Collider::SetDimensions(const SDL_Rect& rect)
{
	m_Rect = rect;
}

void dae::Collider::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

const std::vector<dae::Collider*>& dae::Collider::GetColliders()
{
	return GetGameObject()->GetScene()->GetColliders();
}

const std::string& dae::Collider::GetTag() const
{
	return m_Tag;
}

void dae::Collider::SetOffset(int x, int y)
{
	m_Offset.x = x;
	m_Offset.y = y;
}