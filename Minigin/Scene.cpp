#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	object->SetScene(this);
	m_pObjects.emplace_back(std::move(object));
}

void dae::Scene::AddRenderComponent(dae::RenderComponent* pRenderComponent)
{
	m_pRenderComponents.push_back(pRenderComponent);
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), object), m_pObjects.end());
}

void dae::Scene::RemoveRenderComponent(dae::RenderComponent* pRenderComponent)
{
	m_pRenderComponents.erase(std::remove(m_pRenderComponents.begin(), m_pRenderComponents.end(), pRenderComponent), m_pRenderComponents.end());
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

	for (auto& object : m_pObjects)
	{
		object->RemoveMarkedComponents();
	}
}

void dae::Scene::LateUpdate()
{
	for (auto& object : m_pObjects)
	{
		object->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& c : m_pRenderComponents)
	{
		c->Render();
	}
}

