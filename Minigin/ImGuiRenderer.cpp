#include "ImGuiRenderer.h"
#include <imgui.h>
#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_sdl2.h>
#include "Renderer.h"

dae::ImGuiRenderer::ImGuiRenderer(GameObject* pGameObject)
	: dae::RenderComponent(pGameObject)
{

}

dae::ImGuiRenderer::~ImGuiRenderer()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void dae::ImGuiRenderer::Loaded()
{
	RenderComponent::Loaded();
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(Renderer::GetInstance().GetSDLWindow(), SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::ImGuiRenderer::Render() const
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(Renderer::GetInstance().GetSDLWindow());
	ImGui::NewFrame();

	for (auto& DrawWindow : m_WindowFunctions)
		DrawWindow();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void dae::ImGuiRenderer::AddWindowFunction(std::function<void()> function)
{
	if (function == nullptr)
		return;

	m_WindowFunctions.push_back(function);
}

void dae::ImGuiRenderer::RemoveWindowFunction(std::function<void()> function)
{
	if (function == nullptr)
		return;

	auto it = std::find_if(begin(m_WindowFunctions), end(m_WindowFunctions), [&](const std::function<void()>& f)
		{
			return f.target_type() == function.target_type();
		});

	if (it != end(m_WindowFunctions))
	{
		m_WindowFunctions.erase(it);
	}
}
