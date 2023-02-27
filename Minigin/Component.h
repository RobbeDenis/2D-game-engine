#pragma once
#include "GameObject.h"
#include <memory>

namespace dae
{
	class Component
	{
	public:
		Component(GameObject* pGameObject);
		virtual ~Component() = default;

		void Destroy();
		
		virtual void Loaded() {};
		virtual void Start() {};
		virtual void Update() {};
		virtual void LateUpdate() {};

	protected:
		GameObject* m_pGameObject;

	private:
		bool m_MarkedForDestroy;
	};
}
