#pragma once
#include <Component.h>

namespace dae
{
	class RotateParent final : public Component
	{
	public:
		RotateParent(GameObject* pGameObject);

		void Update() override;

		void SetSpeed(float speed);
		void SetDirection(int direction);

	private:
		float m_Speed;
		int m_Direction;
	};
}