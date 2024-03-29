#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include <imgui.h>
#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_sdl2.h>

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();
	
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	SceneManager::GetInstance().RenderImGui();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& src, const SDL_Rect& dst, SDL_RendererFlip flip) const
{
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, 0, nullptr, flip);
}

void dae::Renderer::RenderMaskedTexture(const Texture2D& texture, SDL_Texture* mask, SDL_Texture* target, float x, float y, int width, int height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = width;
	dst.h = height;

	SDL_SetRenderTarget(GetSDLRenderer(), target);

	SDL_SetRenderDrawColor(GetSDLRenderer(), 0, 0, 0, 0);
	SDL_RenderClear(GetSDLRenderer());

	SDL_RenderCopy(GetSDLRenderer(), mask, nullptr, nullptr);

	SDL_SetTextureBlendMode(texture.GetSDLTexture(), SDL_BLENDMODE_MUL);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, nullptr);

	SDL_SetRenderTarget(GetSDLRenderer(), nullptr);

	SDL_SetTextureBlendMode(target, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(GetSDLRenderer(), target, nullptr, &dst);
}

void dae::Renderer::RenderLine(int x1, int y1, int x2, int y2, const SDL_Color& color) const
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(GetSDLRenderer(), x1, y1, x2, y2);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }