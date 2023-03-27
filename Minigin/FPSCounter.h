#pragma once
#include "Component.h"

namespace dae
{
	class TextRenderer;

	class FPSCounter final : public Component
	{
	public:
		FPSCounter(GameObject* pGameObject);

		void Loaded() override;
		void Start() override;
		void Update() override;

		void SetUpdateInterval(float interval);

	private:
		TextRenderer* m_pText;
		float m_UpdateInterval;
		float m_CurruntUpdateInterval;
	};
}