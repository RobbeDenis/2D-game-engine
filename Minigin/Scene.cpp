#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"

using namespace dae;

Scene::Scene(const std::string& name, unsigned int id)
	: m_Name{name}
	, m_Id{id}
{
}

dae::Scene::~Scene()
{
}

GameObject* dae::Scene::CreateGameObject()
{
	std::unique_ptr<GameObject> object = std::make_unique<GameObject>();
	GameObject* raw = object.get();
	raw->SetScene(this);
	m_pObjects.push_back(std::move(object));
	return raw;
}

GameObject* dae::Scene::CreateGameObject(const std::string& name)
{
	std::unique_ptr<GameObject> object = std::make_unique<GameObject>(name);
	GameObject* raw = object.get();
	raw->SetScene(this);
	m_pObjects.push_back(std::move(object));
	return raw;
}

void dae::Scene::AddCollider(Collider* pCollider)
{
	m_pColliders.push_back(pCollider);
}

void dae::Scene::RemoveCollider(Collider* pCollider)
{
	if (m_pColliders.empty())
		return;

	m_pColliders.erase(std::remove(begin(m_pColliders), end(m_pColliders), pCollider), end(m_pColliders));
}

void dae::Scene::Add(std::unique_ptr<GameObject>& gameObject)
{
	gameObject->SetScene(this);
	m_pObjects.push_back(std::move(gameObject));
}

void Scene::Remove(const std::unique_ptr<GameObject>& gameObject)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), gameObject), m_pObjects.end());
}

std::vector<Collider*>& dae::Scene::GetColliders()
{
	return m_pColliders;
}

void dae::Scene::AddRenderComponent(RenderComponent* pRenderComponent)
{
	m_pRenderComponents.push_back(pRenderComponent);
}

void dae::Scene::RemoveRenderComponent(RenderComponent* pRenderComponent)
{
	if (m_pRenderComponents.empty())
		return;

	m_pRenderComponents.erase(std::remove(begin(m_pRenderComponents), end(m_pRenderComponents), pRenderComponent), end(m_pRenderComponents));
}

void dae::Scene::AddImGuiComponent(RenderComponent* pImGuiComponent)
{
	m_pImGuiComponents.push_back(pImGuiComponent);
}

void dae::Scene::RemoveImGuiComponent(RenderComponent* pImGuiComponent)
{
	if (m_pImGuiComponents.empty())
		return;

	m_pImGuiComponents.erase(std::remove(begin(m_pImGuiComponents), end(m_pImGuiComponents), pImGuiComponent), end(m_pImGuiComponents));
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

void dae::Scene::Loaded()
{
	for (auto& object : m_pObjects)
	{
		object->Loaded();
	}
}

void dae::Scene::Start()
{
	for (auto& object : m_pObjects)
	{
		object->Start();
	}
}

void Scene::Update()
{
	for(auto& object : m_pObjects)
	{
		object->Update();
	}
}

void dae::Scene::LateUpdate()
{
	for (auto& object : m_pObjects)
	{
		object->LateUpdate();
	}

	for (auto& object : m_pObjects)
	{
		if (object->IsMarkedForDestroy())
		{
			Remove(object);
		}
		else
		{
			object->RemoveMarkedChildren();
			object->RemoveMarkedComponents();
		}
	}
}

void Scene::Render() const
{
	for (const auto& c : m_pRenderComponents)
	{
		c->Render();
	}
}

void dae::Scene::RenderImGui() const
{
	for (const auto& c : m_pImGuiComponents)
	{
		c->Render();
	}
}