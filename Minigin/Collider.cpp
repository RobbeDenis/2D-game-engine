#include "Collider.h"
#include "GameObject.h"
#include "Scene.h"

dae::Collider::Collider(GameObject* pGameObject)
	: Component(pGameObject)
	, m_Rect{ }
	, m_Tag{ "none"}
	, m_Dirty{ true }
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
	SDL_Rect otherRect{ other->GetRect() };
	SDL_Rect thisRect{ GetRect() };

	return (thisRect.x > otherRect.x + otherRect.w ||
		thisRect.x + thisRect.w < otherRect.x ||
		thisRect.y > otherRect.y + otherRect.h ||
		thisRect.y + thisRect.h < otherRect.y);
}

const SDL_Rect& dae::Collider::GetRect()
{
	if (m_Dirty)
	{
		m_Rect.x = static_cast<int>(GetGameObject()->GetWorldPosition().x);
		m_Rect.y = static_cast<int>(GetGameObject()->GetWorldPosition().y);
		m_Dirty = false;
	}

	return m_Rect;
}

void dae::Collider::SetDimensions(int w, int h)
{
	SetDimensions({ 0, 0, w, h });
}

void dae::Collider::SetDimensions(const SDL_Rect& rect)
{
	m_Rect = rect;
	m_Dirty = true;
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