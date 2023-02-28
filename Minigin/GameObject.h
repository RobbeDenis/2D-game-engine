#pragma once
#include <memory>
#include <vector>
#include <string>
#include <concepts>
#include <iostream>
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class Component;
	class Scene;

	template<typename T>
	concept IsComponent = requires(T c)
	{
		{ c } -> std::convertible_to<Component>;
	};

	// todo: this should become final.
	class GameObject 
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Loaded();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render() const;

		void RemoveMarkedComponents();
		void SetDirtyComponentDestroy();

		void SetScene(Scene* scene);
		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		Scene* GetScene() const;
		Transform& GetTransform();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};

		std::vector<std::shared_ptr<Component>> m_pComponents;
		Scene* m_pScene;
		bool m_DirtyComponentDestroy;

	public:
		template<IsComponent T>
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> component = std::make_shared<T>(this);
			m_pComponents.push_back(component);
			return component;
		}

		template<IsComponent T>
		std::shared_ptr<T> GetComponent() const
		{
			auto it = std::find_if(begin(m_pComponents), end(m_pComponents), [](std::shared_ptr<Component> c)
				{
					return dynamic_pointer_cast<T>(c);
				});

			if (it == end(m_pComponents))
			{
				std::cout << "Warning: std::shared_ptr<T> GetComponent() const, Component has not been found" << std::endl;
				return nullptr;
			}

			return dynamic_pointer_cast<T>(*it);
		}

		void RemoveComponent(std::shared_ptr<Component> component)
		{
			m_pComponents.erase(std::remove(begin(m_pComponents), end(m_pComponents), component), end(m_pComponents));
		}
	};
}
