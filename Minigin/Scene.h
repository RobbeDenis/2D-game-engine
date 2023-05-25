#pragma once
#include <memory>
#include <vector>
#include <string>
#include "GameObject.h"

namespace dae
{
	class RenderComponent;
	class Collider;
	class Scene final
	{
		friend void GameObject::DetachChild(GameObject* child);
	public:
		explicit Scene(const std::string& name, unsigned int id);
		~Scene();

		void Loaded();
		void Start();
		void Update();
		void LateUpdate();
		void Render() const;
		void RenderImGui() const;

		GameObject* CreateGameObject();
		GameObject* CreateGameObject(const std::string& name);

		void AddCollider(Collider* pCollider);
		void RemoveCollider(Collider* pCollider);
		void AddRenderComponent(RenderComponent* pRenderComponent);
		void RemoveRenderComponent(RenderComponent* pRenderComponent);
		void AddImGuiComponent(RenderComponent* pRenderComponent);
		void RemoveImGuiComponent(RenderComponent* pRenderComponent);
		void RemoveAll();

		const std::string& GetName() const { return m_Name;	};
		unsigned int GetId() const { return m_Id;	};

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		void Add(std::unique_ptr<GameObject>& gameObject);
		void Remove(const std::unique_ptr<GameObject>& gameObject);
		friend Collider;
		std::vector<Collider*>& GetColliders();

		unsigned int m_Id;
		std::string m_Name;
		std::vector<std::unique_ptr<GameObject>> m_pObjects;
		std::vector<RenderComponent*> m_pRenderComponents;
		std::vector<RenderComponent*> m_pImGuiComponents;
		std::vector<Collider*> m_pColliders;
	};

}
