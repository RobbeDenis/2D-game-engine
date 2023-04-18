#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class TestCharacter : public Component , public Subject
	{
	public:
		TestCharacter(GameObject* gameObject);

		void Start() override;

		void SetMaxLives(int lives);
		void Kill();

		int GetLives() const;

		void TestEvent(unsigned event);

	private:
		int m_MaxLives;
		int m_Lives;
	};
}