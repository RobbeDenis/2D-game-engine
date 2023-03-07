#include "GameObject.h"
#include "Component.h"

dae::GameObject::GameObject()
	: GameObject("")
{

}

dae::GameObject::GameObject(const std::string& label)
	: m_Label{ label }
	, m_pParent{ nullptr }
	, m_pScene{ nullptr }
	, m_WorldPosition{ }
	, m_LocalPosition{ }
	, m_PositionIsDirty{ false }
	, m_IsMarkedForDestroy{ false }
	, m_HasComponentsMarkedForDestroy{ false }
{

}

dae::GameObject::~GameObject()
{

}

std::weak_ptr<dae::GameObject> dae::GameObject::AddChild()
{
	return AddChild("");
}

std::weak_ptr<dae::GameObject> dae::GameObject::AddChild(const std::string& label)
{
	std::shared_ptr<dae::GameObject> child = std::make_shared<dae::GameObject>(label);
	child->m_pParent = this;
	child->UpdateWorldPosition();
	m_pChildren.push_back(child);
	return child;
}

void dae::GameObject::Destroy()
{
	m_IsMarkedForDestroy = true;
}

void dae::GameObject::Loaded()
{
	for (auto& c : m_pComponents)
	{
		c->Loaded();
	}

	for (auto& child : m_pChildren)
	{
		child->Loaded();
	}
}

void dae::GameObject::Start()
{
	for (auto& c : m_pComponents)
	{
		c->Start();
	}

	for (auto& child : m_pChildren)
	{
		child->Start();
	}
}

void dae::GameObject::Update()
{
	for (auto& c : m_pComponents)
	{
		c->Update();
	}

	for (auto& child : m_pChildren)
	{
		child->Update();
	}
}

void dae::GameObject::LateUpdate()
{
	for (auto& c : m_pComponents)
	{
		c->LateUpdate();
	}

	for (auto& child : m_pChildren)
	{
		child->LateUpdate();
	}
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	SetLocalPosition({ x, y, 0.f });
}

void dae::GameObject::SetLocalPosition(const glm::vec3& position)
{
	m_LocalPosition = position;
	m_PositionIsDirty = true;
}

const glm::vec3 dae::GameObject::GetWorldPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();

	return m_WorldPosition;
}

const glm::vec3 dae::GameObject::GetLocalPosition() const
{
	return m_LocalPosition;
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
		if (m_pParent == nullptr)
			m_WorldPosition = m_LocalPosition;
		else
			m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;
	}
	m_PositionIsDirty = false;
}

void dae::GameObject::RemoveMarkedComponents()
{
	if (m_HasComponentsMarkedForDestroy)
	{
		for (auto& c : m_pComponents)
		{
			if (c->IsMarkedForDestroy())
			{
				RemoveComponent(c);
			}
		}

		m_HasComponentsMarkedForDestroy = false;
	}

	for (auto& child : m_pChildren)
	{
		child->RemoveMarkedComponents();
	}
}

void dae::GameObject::SetComponentsMarkedForDestroy()
{
	m_HasComponentsMarkedForDestroy = true;
}

bool dae::GameObject::IsMarkedForDestroy() const
{
	return m_IsMarkedForDestroy;
}

dae::Scene* dae::GameObject::GetScene() const
{
	if (m_pParent == nullptr)
		return m_pScene;

	return m_pParent->GetScene();
}

void dae::GameObject::SetScene(Scene* scene)
{
	m_pScene = scene;
}