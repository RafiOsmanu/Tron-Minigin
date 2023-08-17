#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl2.h"
#include "imgui_plot.h"
#include "RenderPlot.h"


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
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
	//ImGui::SetWindowSize(ImVec2(50, 20));
	

	/*m_Config = std::unique_ptr<RenderPlot>(new RenderPlot);
	m_Config->MeasureIntListCreation(10);
	m_Config->MeasureGameObject3D();
	m_Config->MeasureGameObject3DAlt();*/
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);
	SceneManager::GetInstance().Render();

	//render IMGUI
	/*ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();*/

	//DO NOT HARD CODE THE PLOT 
	//TO DO: MAKE THE PLOT A COMPONENT
	
	//Plot ex1
	//ImGui::Begin("Exercise 1");
	//ImGui::Plot("plot", m_Config->GetConfigEx1());
	//ImGui::End();

	////Plot ex1
	//ImGui::Begin("Exercise 2");
	//ImGui::Plot("plot", m_Config->GetConfigEx2());
	//ImGui::Plot("plot", m_Config->GetConfigEx3());
	//ImGui::End();
	
	

	//ImGui::ShowDemoWindow();
	/*ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());*/

	
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::DrawRect(const SDL_Rect& rect) const
{
	SDL_RenderDrawRect(m_renderer, &rect);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
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

void dae::Renderer::RenderTexture(const Texture2D& texture, float x, float y, const float rotationAngle, bool mirror) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	//dst.w = static_cast<int>(width);
	//dst.h = static_cast<int>(height);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

	SDL_Point center{};
	center.x = dst.w / 2;
	center.y = dst.h / 2;

	SDL_RendererFlip flip; // You can use SDL_FLIP_HORIZONTAL or SDL_FLIP_VERTICAL if you want to flip the texture
	if (mirror)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		flip = SDL_FLIP_NONE;
	}

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, rotationAngle, &center, flip);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, float x, float y, float width, float height, const float rotationAngle, bool mirror) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	
	SDL_Point center{};
	center.x = dst.w / 2;
	center.y = dst.h / 2;

	SDL_RendererFlip flip; // You can use SDL_FLIP_HORIZONTAL or SDL_FLIP_VERTICAL if you want to flip the texture
	if (mirror)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		flip = SDL_FLIP_NONE;
	}

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, rotationAngle, &center, flip);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
