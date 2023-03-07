#include "GameObject.h"
#include "Component.h"

using namespace dae;

dae::GameObject::GameObject()
	: m_Transform{ }
	, m_pScene{ nullptr }
	, m_IsMarkedForDestroy{ false }
	, m_HasComponentsMarkedForDestroy{ false }
{

}

dae::GameObject::~GameObject()
{
	for (auto& c : m_pComponents)
	{
		c->Loaded();
	}
}

void dae::GameObject::Destroy()
{
	m_IsMarkedForDestroy = true;
}

void GameObject::Loaded()
{
	for (auto& c : m_pComponents)
	{
		c->Loaded();
	}
}

void GameObject::Start()
{
	for (auto& c : m_pComponents)
	{
		c->Start();
	}
}

void GameObject::Update()
{
	for (auto& c : m_pComponents)
	{
		c->Update();
	}
}

void GameObject::LateUpdate()
{
	for (auto& c : m_pComponents)
	{
		c->LateUpdate();
	}
}

void dae::GameObject::RemoveMarkedComponents()
{
	if (!m_HasComponentsMarkedForDestroy)
		return;

	for (auto& c : m_pComponents)
	{
		if (c->IsMarkedForDestroy())
		{
			RemoveComponent(c);
		}
	}

	m_HasComponentsMarkedForDestroy = false;
}

void dae::GameObject::SetComponentsMarkedForDestroy()
{
	m_HasComponentsMarkedForDestroy = true;
}

bool dae::GameObject::IsMarkedForDestroy() const
{
	return m_IsMarkedForDestroy;
}

Scene* dae::GameObject::GetScene() const
{
	return m_pScene;
}

Transform& dae::GameObject::GetTransform()
{
	return m_Transform;
}

void dae::GameObject::SetScene(Scene* scene)
{
	m_pScene = scene;
}