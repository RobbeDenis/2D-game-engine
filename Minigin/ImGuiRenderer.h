#pragma once
#include "RenderComponent.h"
#include <functional>

namespace dae
{
	class ImGuiRenderer final : public RenderComponent
	{
	public:
		ImGuiRenderer(GameObject* pGameObject);
		~ImGuiRenderer();

		void Loaded() override;
		void Render() const override;

		void AddWindowFunction(std::function<void()> function);

	private:
		std::vector<std::function<void()>> m_WindowFunctions;
	};
}