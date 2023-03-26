#include "ImGuiRenderer.h"

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

//void dae::ImGuiRenderer::RemoveWindowFunction(std::function<void()> function)
//{
//	if (function == nullptr)
//		return;
//
//	auto it = std::find_if(begin(m_WindowFunctions), end(m_WindowFunctions), [&](const std::function<void()>& f)
//		{
//			return f.target_type() == function.target_type();
//		});
//
//	if (it != end(m_WindowFunctions))
//	{
//		m_WindowFunctions.erase(it);
//	}
//}
