#pragma once
#include "Component.h"
namespace dae
{
	class TestCharacter : public Component
	{
	public:
		TestCharacter(GameObject* gameObject);

		void SetMaxLives(int lives);
		void Kill();

	private:
		int m_Lives;
	};
}