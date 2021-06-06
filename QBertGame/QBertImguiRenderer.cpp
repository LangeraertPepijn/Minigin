#include "QBertPCH.h"
#include "QBertImguiRenderer.h"
#include <SDL_render.h>
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

void QBertImguiRenderer::Init(SDL_Window* window)
{
	m_pWindow = window;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void QBertImguiRenderer::RenderUI()
{
	
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame(m_pWindow);
		ImGui::NewFrame();
		ImGui::Begin("Controls");
		ImGui::Text("player1: press  wasd or controller 1 dpad to move\n");
		ImGui::Text("player1: press  1379 or controller 2 dpad to move\n");
		if(ImGui::Button("SinglePlayer"))
		{
			m_GameMode = GameMode::SinglePlayer;
		}
		if(ImGui::Button("Co-Op"))
		{
			
			m_GameMode = GameMode::MultiPlayerCoop;
		}
		if(ImGui::Button("Versus"))
		{
			
			m_GameMode = GameMode::MultiPlayerVS;
		}
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void QBertImguiRenderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
}

GameMode QBertImguiRenderer::GetGameMode()
{
	return m_GameMode;
}
