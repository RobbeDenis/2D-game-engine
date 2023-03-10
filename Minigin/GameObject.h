#pragma once
#include "Scene.h"
#include <memory>
#include <vector>
#include <concepts>
#include <iostream>
#include <glm/glm.hpp>

namespace dae
{
	class Component;
	class GameObject;

	template<typename T>
	concept IsComponent = std::is_base_of_v<Component, T> && requires(GameObject* gameObject)
	{
		new T(gameObject);
	};

	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
		friend void Scene::Add(std::shared_ptr<GameObject> object);
	public:
		GameObject();
		GameObject(const std::string& label);
		virtual ~GameObject();

		void Destroy();

		virtual void Loaded();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();

		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec3& position);
		const glm::vec3 GetWorldPosition();
		const glm::vec3 GetLocalPosition() const;

		std::weak_ptr<GameObject> GetChild(size_t index) const;
		std::weak_ptr<GameObject> GetChild(const std::string& label) const;
		std::weak_ptr<GameObject> AddChild();
		std::weak_ptr<GameObject> AddChild(const std::string& label);
		void AttachChild(std::weak_ptr<GameObject> child, bool keepWorldPosition = false);
		void DetachChild(std::weak_ptr<GameObject> child, bool addToScene = true);
		size_t GetAmountOffChildren() const;

		void RemoveMarkedChildren();
		void RemoveMarkedComponents();
		void SetComponentsMarkedForDestroy();
		bool IsMarkedForDestroy() const;

		Scene* GetScene();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		void SetScene(Scene* scene);
		bool RemoveChild(std::shared_ptr<GameObject> child);
		void SetChildrenMarkedForDestroy();
		void UpdateWorldPosition();

		std::string m_Label;
		std::vector<std::shared_ptr<Component>> m_pComponents;
		std::vector<std::shared_ptr<GameObject>> m_pChildren;
		GameObject* m_pParent;
		Scene* m_pScene;
		glm::vec3 m_WorldPosition;
		glm::vec3 m_LocalPosition;
		bool m_PositionIsDirty;
		bool m_IsMarkedForDestroy;
		bool m_HasChildrenMarkedForDestroy;
		bool m_HasComponentsMarkedForDestroy;

	public:
		template<IsComponent T>
		std::weak_ptr<T> AddComponent()
		{
			std::shared_ptr<T> component = std::make_shared<T>(this);
			m_pComponents.push_back(component);
			return component;
		}

		template<IsComponent T>
		std::weak_ptr<T> GetComponent() const
		{
			for (auto& component : m_pComponents)
			{
				auto casted = std::dynamic_pointer_cast<T>(component);
				if (casted)
					return casted;
			}
			return std::weak_ptr<T>();
		}

	private:
		void RemoveComponent(std::shared_ptr<Component> component)
		{
			m_pComponents.erase(std::remove(begin(m_pComponents), end(m_pComponents), component), end(m_pComponents));
		}
	};
}
