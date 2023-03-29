#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class Movement final : public Component
	{
	public:
		Movement(GameObject* gameObject);

		void Update() override;

		void SetMovementSpeed(float speed) { m_MovementSpeed = speed; };
		void Move(int x, int y);

	private:
		glm::vec2 m_Direction;
		float m_MovementSpeed;
		bool m_ShouldMove;
	};
}