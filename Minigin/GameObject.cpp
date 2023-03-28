#include "GameObject.h"
#include "Scene.h"

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
	, m_HasChildrenMarkedForDestroy{ false }
	, m_HasComponentsMarkedForDestroy{ false }
{

}

dae::GameObject::~GameObject()
{

}

dae::GameObject* dae::GameObject::GetChild(size_t index) const
{
	if (index >= m_pChildren.size())
		return nullptr;

	return m_pChildren[index].get();
}

dae::GameObject* dae::GameObject::GetChild(const std::string& label) const
{
	auto it = std::find_if(begin(m_pChildren), end(m_pChildren), [&label](auto& child)
		{
			return child->m_Label == label;
		});

	if (it == end(m_pChildren))
		return nullptr;

	return it->get();
}

dae::GameObject* dae::GameObject::AddChild()
{
	return AddChild("");
}

dae::GameObject* dae::GameObject::AddChild(const std::string& label)
{
	std::unique_ptr<dae::GameObject> child = std::make_unique<dae::GameObject>(label);
	child->m_pParent = this;
	child->m_PositionIsDirty = true;
	GameObject* raw = child.get();
	m_pChildren.push_back(std::move(child));
	return raw;
}

bool dae::GameObject::RemoveChild(GameObject* child)
{
	auto it = std::find_if(begin(m_pChildren), end(m_pChildren), [&](const std::unique_ptr<GameObject>& c)
		{
			return c.get() == child;
		});

	if (it == end(m_pChildren))
		return false;

	m_pChildren.erase(it);
	return true;
}

void dae::GameObject::DetachChild(GameObject* child)
{
	if (child == nullptr || child == this)
		return;

	auto it = std::find_if(begin(m_pChildren), end(m_pChildren), [&](const std::unique_ptr<GameObject>& c)
		{
			return c.get() == child;
		});

	if (it == end(m_pChildren))
		return;

	child->m_pParent = nullptr;
	child->SetLocalPosition(GetWorldPosition() + child->GetLocalPosition());

	GetScene()->Add(*it);
	m_pChildren.erase(it);
}

void dae::GameObject::AttachChild(GameObject* child, bool keepWorldPosition)
{
	if (child == nullptr || child == this)
		return;
	
	if (keepWorldPosition)
	{
		child->SetLocalPosition(child->GetWorldPosition() - GetWorldPosition());
	}

	if (child->m_pParent == nullptr)
	{
		throw std::runtime_error("Attempting to add child with no parent, consider using AddChild() instead");
	}

	GameObject* parent = child->m_pParent;
	auto it = std::find_if(begin(parent->m_pChildren), end(parent->m_pChildren), [&](const std::unique_ptr<GameObject>& c)
		{
			return c.get() == child;
		});
	if (it == end(parent->m_pChildren))
		throw std::runtime_error("Child was not found in parent");

	m_pChildren.push_back(std::move(*it));
	parent->m_pChildren.erase(it);

	child->m_pParent = this;
}

void dae::GameObject::Destroy()
{
	if (m_pParent != nullptr)
		m_pParent->SetChildrenMarkedForDestroy();

	m_IsMarkedForDestroy = true;
}

void dae::GameObject::SetChildrenMarkedForDestroy()
{
	if (m_pParent != nullptr)
		m_pParent->SetChildrenMarkedForDestroy();

	m_HasChildrenMarkedForDestroy = true;
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

size_t dae::GameObject::GetAmountOffChildren() const
{
	return m_pChildren.size();
}

void dae::GameObject::RemoveMarkedChildren()
{
	if (!m_HasChildrenMarkedForDestroy)
		return;

	m_pChildren.erase(std::remove_if(begin(m_pChildren), end(m_pChildren), [](auto& child)
		{
			if (child->IsMarkedForDestroy())
			{
				return true;
			}
			else if (child->m_HasChildrenMarkedForDestroy)
			{
				child->RemoveMarkedChildren();
			}

			return false;
		}), end(m_pChildren));

	m_HasChildrenMarkedForDestroy = false;
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

dae::Scene* dae::GameObject::GetScene()
{
	if (m_pParent == nullptr)
		return m_pScene;

	return m_pParent->GetScene();
}

void dae::GameObject::SetScene(Scene* scene)
{
	m_pScene = scene;
}