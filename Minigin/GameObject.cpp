#include "GameObject.h"
#include "Component.h"

using namespace dae;

dae::GameObject::GameObject()
	: m_Transform{ }
	, m_pScene{ nullptr }
	, m_DirtyComponentDestroy{ false }
{

}

dae::GameObject::~GameObject()
{

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
	if (!m_DirtyComponentDestroy)
		return;

	for (auto& c : m_pComponents)
	{
		if (c->IsMarkedForDestroy())
		{
			RemoveComponent(c);
		}
	}

	m_DirtyComponentDestroy = false;
}

void dae::GameObject::SetDirtyComponentDestroy()
{
	m_DirtyComponentDestroy = true;
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