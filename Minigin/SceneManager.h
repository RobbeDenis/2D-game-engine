#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "Scene.h"

namespace dae
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void Loaded();
		void Start();
		void Update();
		void LateUpdate();
		void Render() const;
		void RenderImGui() const;

		Scene* CreateScene(const std::string& name);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_pScenes;
	};
}
