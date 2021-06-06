#pragma once
#include <Singleton.h>
#include "GameMode.h"
struct SDL_Window;
struct SDL_Renderer;
class Texture2D;
class QBertImguiRenderer final : public Singleton<QBertImguiRenderer>
{
public:
	void Init(SDL_Window* window);
	void RenderUI();
	void Destroy();
	GameMode GetGameMode();
private:
	SDL_Window* m_pWindow{};
	GameMode m_GameMode{GameMode::SinglePlayer };
};