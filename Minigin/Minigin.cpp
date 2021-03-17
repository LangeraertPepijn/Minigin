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
#include "Components.h"
#include "PlayerObserver.h"
#include "Subject.h"

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

	//backGround
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared <TextureComponent>(go, "background.jpg"));
	go->AddComponent(std::make_shared <RenderComponent>(go));
	scene.Add(go);

	// logo
	go = std::make_shared<GameObject>(glm::vec3(216.f, 180.f, 0.f));
	go->AddComponent(std::make_shared <TextureComponent>(go, "logo.png"));
	go->AddComponent(std::make_shared <RenderComponent>(go));
	scene.Add(go);

	//text
	go = std::make_shared<GameObject>(glm::vec3(80.f, 20.f, 0.f));
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(std::make_shared <TextComponent>(go, "Programming 4 Assignment", font));
	go->AddComponent(std::make_shared <RenderComponent>(go));
	scene.Add(go);


	go = std::make_shared<GameObject>(glm::vec3(5.f, 5.f, 0.f));
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	go->AddComponent(std::make_shared <TextComponent>(go, " ", font,glm::tvec3<uint8_t> { 255,255,0 }));
	go->AddComponent(std::make_shared <FpsComponent>(go));
	go->AddComponent(std::make_shared <RenderComponent>(go));
	scene.Add(go);
	

	//Player1

	go = std::make_shared<GameObject>(glm::vec3(100.f, 5.f, 0.f));
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto txt =std::make_shared <TextComponent>(go, " lives p1", font, glm::tvec3<uint8_t> { 255, 255, 0 });
	go->AddComponent(txt);
	go->AddComponent(std::make_shared <RenderComponent>(go));
	go->AddComponent(std::make_shared <HealthComponent>(go,10));
	auto scoreComponent = std::make_shared <ScoreComponent>(go);
	go->AddComponent(scoreComponent);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_1, ExecuteType::Pressed, std::make_shared<DamageCommand>(go,1));
	std::shared_ptr<Subject> subject = std::make_shared<Subject>();


	
	auto go2 = std::make_shared<GameObject>(glm::vec3(100.f, 25.f, 0.f));
	auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto txt2 = std::make_shared <TextComponent>(go2, " score p2", font, glm::tvec3<uint8_t> { 255, 255, 0 });
	go2->AddComponent(txt2);
	go2->AddComponent(std::make_shared <RenderComponent>(go2));
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_2, ExecuteType::Pressed, std::make_shared<ScoreCommand>(scoreComponent, 1));
	go2->SetSubject(subject);



	std::shared_ptr<PlayerObserver> player1 = std::make_shared<PlayerObserver>(go, go2);
	go->SetSubject(subject);

	subject->AddObserver(player1);
	go->SetSubject(subject);
	scene.Add(go2);
	scene.Add(go);
	//Player2

	go = std::make_shared<GameObject>(glm::vec3(100.f, 45.f, 0.f));
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	txt = std::make_shared <TextComponent>(go, " lives p2", font, glm::tvec3<uint8_t> { 255, 255, 0 });
	go->AddComponent(txt);
	go->AddComponent(std::make_shared <RenderComponent>(go));
	go->AddComponent(std::make_shared <HealthComponent>(go, 10));
	scoreComponent = std::make_shared <ScoreComponent>(go);
	go->AddComponent(scoreComponent);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_3, ExecuteType::Pressed, std::make_shared<DamageCommand>(go, 1));
	


	go2 = std::make_shared<GameObject>(glm::vec3(100.f, 65.f, 0.f));
	font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	txt2 = std::make_shared <TextComponent>(go2, " score p2", font, glm::tvec3<uint8_t> { 255, 255, 0 });
	go2->AddComponent(txt2);
	go2->AddComponent(std::make_shared <RenderComponent>(go2));
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_4, ExecuteType::Pressed, std::make_shared<ScoreCommand>(scoreComponent, 1));



	std::shared_ptr<PlayerObserver> player2 = std::make_shared<PlayerObserver>(go, go2);
	subject->AddObserver(player2);
	go->SetSubject(subject);
	go2->SetSubject(subject);

	scene.Add(go);

	scene.Add(go2);

	
	
	
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
	bool* quit{ new bool{} };
	//InputManager::GetInstance().AddCommand(SDL_SCANCODE_0, ExecuteType::Released, std::make_shared<QuitCommand>(quit));

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto lastTime = high_resolution_clock::now();

		bool doContinue = true;

		while (doContinue&&!*quit)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = duration<float>(currentTime - lastTime).count();

			lastTime = currentTime;
			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			renderer.Render();
			
			//auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			//this_thread::sleep_for(sleepTime);
		}
	}
	delete quit;

	Cleanup();
}
