#pragma once
#include "Component.h"

namespace dae
{
	class ImGuiRenderer;
	class TrashTheCash final : public Component
	{
	public:
		TrashTheCash(GameObject* gameObject);
		~TrashTheCash();

		void Loaded() override;
		void Start() override;

	private:
		void Exercise1();
		void Exercise2();
		void Exercise2Alt();

		void Exercise1Window();
		void Exercise2Window();

		std::vector<float> m_Ex1Data;
		std::vector<float> m_Ex2Data;
		std::vector<float> m_Ex2DataAlt;
		std::weak_ptr<ImGuiRenderer> m_pImGui;
		int m_Ex1Samples;
		int m_Ex2Samples;
		float m_OutlierPercentage;
	};
}
