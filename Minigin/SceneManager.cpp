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
	if (id >= static_cast<unsigned int>(m_pScenes.size()))
		throw std::runtime_error("Scene Id is out of range");

	m_CurrentScene = id;

	if (m_GameStarted)
		Start();
}

void dae::SceneManager::SetScene(const std::string& name)
{
	auto it = find_if(begin(m_pScenes), end(m_pScenes), [&](std::unique_ptr<Scene>& scene)
		{
			return scene->GetName() == name;
		});

	if(it == end(m_pScenes))
		throw std::runtime_error("Scene with given name was not found");

	SetScene(it->get()->GetId());
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	std::unique_ptr<Scene> scene = std::make_unique<Scene>(name, static_cast<unsigned int>(m_pScenes.size()));
	Scene* raw = scene.get();
	m_pScenes.push_back(std::move(scene));
	return raw;
}