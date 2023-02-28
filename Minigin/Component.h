#pragma once
#include "GameObject.h"
#include <memory>

namespace dae
{
	class Component
	{
	public:
		Component(GameObject* pGameObject);
		virtual ~Component();

		void Destroy();
		
		virtual void Loaded() {};
		virtual void Start() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void OnDestroy() {};

		bool IsMarkedForDestroy() const;

	protected:
		GameObject* m_pGameObject;

	private:
		bool m_IsMarkedForDestroy;
	};
}
