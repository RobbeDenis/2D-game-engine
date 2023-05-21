#include "ImGuiRenderer.h"
#include "GameObject.h"
#include "Scene.h"

dae::ImGuiRenderer::ImGuiRenderer(GameObject* pGameObject)
	: dae::RenderComponent(pGameObject)
{

}

dae::ImGuiRenderer::~ImGuiRenderer()
{
	
}

void dae::ImGuiRenderer::Loaded()
{
	GetGameObject()->GetScene()->AddImGuiComponent(this);
}

void dae::ImGuiRenderer::Render() const
{
	for (const std::function<void()>& DrawWindow : m_WindowFunctions)
	{
		if (DrawWindow)
			DrawWindow();
	}
}

void dae::ImGuiRenderer::AddWindowFunction(std::function<void()> function)
{
	if (function == nullptr)
		return;

	m_WindowFunctions.push_back(function);
}
