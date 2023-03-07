#pragma once
#include <memory>
#include <vector>
#include <concepts>
#include <iostream>
#include <glm/glm.hpp>

namespace dae
{
	class Component;
	class Scene;
	class GameObject;

	template<typename T>
	concept IsComponent = std::is_base_of_v<Component, T> && requires(GameObject* gameObject)
	{
		new T(gameObject);
	};

	class GameObject final
	{
	public:
		GameObject();
		GameObject(std::string label);
		virtual ~GameObject();

		void Destroy();

		virtual void Loaded();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();

		void SetWorldPosition(float x, float y);
		void SetLocalPosition(float x, float y);
		void SetWorldPosition(const glm::vec3& position);
		void SetLocalPosition(const glm::vec3& position);
		const glm::vec3 GetWorldPosition() const;
		const glm::vec3 GetLocalPosition() const;

		//std::shared_ptr<GameObject> GetChild(int index) const;
		//std::shared_ptr<GameObject> GetChild(const std::string& label) const;
		std::weak_ptr<GameObject> AddChild();
		std::weak_ptr<GameObject> AddChild(const std::string& label);
		//void AttachChild(std::shared_ptr<GameObject> child);
		//void DestroyChild(int index);
		//void DestroyChild(const std::string& label);
		//void DestroyAllChildren();

		void RemoveMarkedComponents();
		void SetComponentsMarkedForDestroy();
		bool IsMarkedForDestroy() const;

		void SetScene(Scene* scene);
		Scene* GetScene() const;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::string m_Label;
		std::vector<std::shared_ptr<Component>> m_pComponents;
		std::vector<std::shared_ptr<GameObject>> m_pChildren;
		GameObject* m_pParent;
		Scene* m_pScene;
		glm::vec3 m_WorldPosition;
		glm::vec3 m_LocalPosition;
		bool m_PositionIsDirty;
		bool m_IsMarkedForDestroy;
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
