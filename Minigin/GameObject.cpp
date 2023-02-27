#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

using namespace dae;

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

void GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}