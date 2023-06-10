#include "SceneManager.h"

dae::SceneManager::SceneManager()
	: m_CurrentScene{ 0 }
	, m_GameStarted{ false }
{
}

void dae::SceneManager::Loaded()
{
	for (auto& scene : m_pScenes)
	{
		scene->Loaded();
	}
}

void dae::SceneManager::Start()
{
	m_pScenes[m_CurrentScene]->Start();
	m_GameStarted = true;
}

void dae::SceneManager::Update()
{
	m_pScenes[m_CurrentScene]->Update();
}

void dae::SceneManager::LateUpdate()
{
	m_pScenes[m_CurrentScene]->LateUpdate();
}

void dae::SceneManager::Render() const
{
	m_pScenes[m_CurrentScene]->Render();
}

void dae::SceneManager::RenderImGui() const
{
	m_pScenes[m_CurrentScene]->RenderImGui();
}

void dae::SceneManager::SetScene(unsigned int id)
{
	auto it = std::find_if(begin(m_pScenes), end(m_pScenes), [id] (auto& scene) 
		{
			return scene->GetId() == id;
		});

	if (it == end(m_pScenes))
		return;

	m_CurrentScene = it->get()->GetId();

	if (m_GameStarted)
		Start();
}

dae::Scene* dae::SceneManager::CreateScene(unsigned id)
{
	std::unique_ptr<Scene> scene = std::make_unique<Scene>(id);
	Scene* raw = scene.get();
	m_pScenes.push_back(std::move(scene));
	return raw;
}