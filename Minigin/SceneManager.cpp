#include "SceneManager.h"

void dae::SceneManager::Loaded()
{
	for (const auto& scene : m_pScenes)
	{
		scene->Loaded();
	}
}

void dae::SceneManager::Start()
{
	for (const auto& scene : m_pScenes)
	{
		scene->Start();
	}
}

void dae::SceneManager::Update()
{
	for(auto& scene : m_pScenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::LateUpdate()
{
	for (const auto& scene : m_pScenes)
	{
		scene->LateUpdate();
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_pScenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::RenderImGui() const
{
	for (const auto& scene : m_pScenes)
	{
		scene->RenderImGui();
	}
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	std::unique_ptr<Scene> scene = std::make_unique<Scene>(name);
	Scene* raw = scene.get();
	m_pScenes.push_back(std::move(scene));
	return raw;
}
