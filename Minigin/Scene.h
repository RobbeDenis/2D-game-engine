#pragma once
#include <memory>
#include <vector>
#include <string>
#include "GameObject.h"

namespace dae
{
	class RenderComponent;

	class Scene final
	{
		friend void GameObject::DetachChild(GameObject* child);
	public:
		explicit Scene(const std::string& name);
		~Scene() = default;

		void Loaded();
		void Start();
		void Update();
		void LateUpdate();
		void Render() const;
		void RenderImGui() const;

		GameObject* CreateGameObject();
		GameObject* CreateGameObject(const std::string& name);
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
		void Add(std::unique_ptr<GameObject>& gameObject);
		void Remove(const std::unique_ptr<GameObject>& gameObject);

		std::string m_Name;
		std::vector<std::unique_ptr<GameObject>> m_pObjects;
		std::vector<RenderComponent*> m_pRenderComponents;
		std::vector<RenderComponent*> m_pImGuiComponents;

		static unsigned int m_idCounter; 
	};

}
