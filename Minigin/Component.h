#pragma once
#include "GameObject.h"
#include <memory>

namespace dae
{
	class Component
	{
	public:
		explicit Component(GameObject* pGameObject);
		virtual ~Component();

		void Destroy();
		
		virtual void Loaded() {};
		virtual void Start() {};
		virtual void Update() {};
		virtual void LateUpdate() {};

		bool IsMarkedForDestroy() const;

		Component() = delete;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;


	protected:
		GameObject* GetGameObject() const;

	private:
		GameObject* m_pGameObject;
		bool m_IsMarkedForDestroy;
	};
}
