#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "TextureComponent.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);



	//logo
	go = std::make_shared<GameObject>();
	go->AddComponent(new TextureComponent(go, "background.jpg"));
	go->AddComponent(new RenderComponent(go, ResourceManager::GetInstance().LoadTexture("background.jpg")));
	scene.Add(go);

	//text
	go = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto temp = go->AddComponent(new TextComponent(go, "Programming 4 Assignment", font));
	auto texComp = dynamic_cast<TextComponent*>(temp);
	go->AddComponent(new TransformComponent(go, glm::vec3(80.f, 20.f, 0.f)));
	go->AddComponent(new RenderComponent(go, texComp->GetTexture()));
	scene.Add(go);

	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto lastTime = high_resolution_clock::now();
		float lag = 0.f;
		bool doContinue = true;

		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = duration<float>(currentTime - lastTime).count();

			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input.ProcessInput();
			while (lag >= MsPerUpdate)
			{
				sceneManager.Update(deltaTime);
				lag -= MsPerUpdate;
			}
			renderer.Render();
			
			//auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			//this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
