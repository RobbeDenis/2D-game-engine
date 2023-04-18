#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class TextRenderer;
	class LivesDisplay : public Component, public Observer
	{
	public:
		explicit LivesDisplay(GameObject* gameObject);

		void Loaded() override;

		void OnNotify(Component* component, unsigned event) override;
	private:
		TextRenderer* m_pText;
	};
}