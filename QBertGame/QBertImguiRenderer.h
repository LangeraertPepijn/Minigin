#pragma once
#include <Singleton.h>
struct SDL_Window;
struct SDL_Renderer;
class Texture2D;
class QBertImguiRenderer final : public Singleton<QBertImguiRenderer>
{
public:
	void Init(SDL_Window* window);
	void RenderUI();
	void Destroy();
private:
	SDL_Window* m_pWindow{};
};