#pragma once
#include <memory>
#include <vector>
#include <string>

namespace dae
{
	class GameObject;
	class RenderComponent;

	class Scene final
	{
	public:
		explicit Scene(const std::string& name);
		~Scene() = default;

		void Loaded();
		void Start();
		void Update();
		void LateUpdate();
		void Render() const;
		void RenderImGui() const;

		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void AddRenderComponent(RenderComponent* pRenderComponent);
		void RemoveRenderComponent(RenderComponent* pRenderComponent);
		void AddImGuiComponent(RenderComponent* pRenderComponent);
		void RemoveImGuiComponent(RenderComponent* pRenderComponent);
		void RemoveAll();

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_pObjects;
		std::vector<RenderComponent*> m_pRenderComponents;
		std::vector<RenderComponent*> m_pImGuiComponents;

		static unsigned int m_idCounter; 
	};

}
