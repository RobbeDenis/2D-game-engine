#pragma once
#include <memory>
#include <vector>
#include <concepts>
#include <iostream>
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class Scene;
	class GameObject;

	template<typename T>
	concept IsComponent = std::is_base_of_v<Component, T>&& requires(GameObject* gameObject)
	{
		new T(gameObject);
	};

	class GameObject final
	{
	public:
		GameObject();
		GameObject(const std::string& label);
		virtual ~GameObject();

		void Destroy();

		virtual void Loaded();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();

		void SetLocalPosition(int x, int y);
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec3& position);
		const glm::vec3 GetWorldPosition();
		const glm::vec3 GetLocalPosition() const;

		GameObject* GetChild(size_t index) const;
		GameObject* GetChild(const std::string& label) const;
		GameObject* AddChild();
		GameObject* AddChild(const std::string& label);
		void AttachChild(GameObject* child, bool keepWorldPosition = false);
		void DetachChild(GameObject* child);
		size_t GetAmountOffChildren() const;

		void RemoveMarkedChildren();
		void RemoveMarkedComponents();
		void SetComponentsMarkedForDestroy();
		bool IsMarkedForDestroy() const;

		void SetScene(Scene* scene);
		Scene* GetScene();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool RemoveChild(GameObject* child);
		void SetChildrenMarkedForDestroy();
		void UpdateWorldPosition();
		void SetDirty();

		std::string m_Label;
		std::vector<std::unique_ptr<Component>> m_pComponents;
		std::vector<std::unique_ptr<GameObject>> m_pChildren;
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
		T* AddComponent()
		{
			std::unique_ptr<T> component = std::make_unique<T>(this);
			T* raw = component.get();
			m_pComponents.push_back(std::move(component));
			return raw;
		}

		template<IsComponent T>
		T* GetComponent() const
		{
			for (const std::unique_ptr<Component>& component : m_pComponents)
			{
				if (T* casted = dynamic_cast<T*>(component.get()))
					return casted;
			}
			return nullptr;
		}

	private:
		void RemoveComponent(const std::unique_ptr<Component>& component)
		{
			m_pComponents.erase(std::remove(begin(m_pComponents), end(m_pComponents), component), end(m_pComponents));
		}
	};
}
