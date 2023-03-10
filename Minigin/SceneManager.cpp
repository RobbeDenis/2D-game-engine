#include "SceneManager.h"
#include "Scene.h"

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

void dae::SceneManager::Render()
{
	for (const auto& scene : m_pScenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_pScenes.push_back(scene);
	return *scene;
}
