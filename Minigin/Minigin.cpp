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
#include "HudObject.h"
#include "HudManager.h"
#include "SDLMixerSoundSystem.h"
#include "ServiceLocator.h"


using namespace std;
using namespace std::chrono;

void Minigin::Initialize()
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
	m_Quit = new bool{};
	UserInitialize();
	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void Minigin::LoadGame() const
{

	UserLoadGame();

	//backGround
	//std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	//go->AddComponent(std::make_shared <TextureComponent>(go, "background.jpg"));
	//go->AddComponent(std::make_shared <RenderComponent>(go));
	//scene.Add(go);
	/*for (int i = 0; i < 7; ++i)
	{
		for (int j =0;j<i;j++)
		{
			if (i % 2 == 1)
			{

				go = std::make_shared<GameObject>();
				go->AddComponent(std::make_shared <TextureComponent>(go, "Cube1.png", glm::vec3(288 + (j-i/2)* 64, 40 + i * 45, 0)));
				go->AddComponent(std::make_shared <RenderComponent>(go));
				scene.Add(go);
			}
			else
			{
				go = std::make_shared<GameObject>();
				go->AddComponent(std::make_shared <TextureComponent>(go, "Cube1.png", glm::vec3(288 + (j - i / 2) * 64 +32, 40 + i * 45, 0)));
				go->AddComponent(std::make_shared <RenderComponent>(go));
				scene.Add(go);
			}
		}
	}*/

	// logo
	//go = std::make_shared<GameObject>(glm::vec3(216.f, 180.f, 0.f));
	//go->AddComponent(std::make_shared <TextureComponent>(go, "logo.png"));
	//go->AddComponent(std::make_shared <RenderComponent>(go));
	//scene.Add(go);

	//text
	//go = std::make_shared<GameObject>(glm::vec3(80.f, 20.f, 0.f));
	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//go->AddComponent(std::make_shared <TextComponent>(go, "Programming 4 Assignment", font));
	//go->AddComponent(std::make_shared <RenderComponent>(go));
	//scene.Add(go);


	//go = std::make_shared<GameObject>(glm::vec3(5.f, 5.f, 0.f));
	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	//go->AddComponent(std::make_shared <TextComponent>(go, " ", font,glm::tvec3<uint8_t> { 255,255,0 }));
	//go->AddComponent(std::make_shared <FpsComponent>(go));
	//go->AddComponent(std::make_shared <RenderComponent>(go));
	//scene.Add(go);
	

	//Player1

	//go = std::make_shared<GameObject>(glm::vec3(100.f, 5.f, 0.f));
	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	//auto txt =std::make_shared <TextComponent>(go, " lives p1", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(100.f, 5.f, 0.f));
	//go->AddComponent(txt);
	////go->AddComponent(std::make_shared <RenderComponent>(go));
	//go->AddComponent(std::make_shared <HealthComponent>(go,10));
	//auto subj1 = std::make_shared <SubjectComponent>(go);
	//go->AddComponent(subj1);
	//auto scoreComponent = std::make_shared <ScoreComponent>(go);
	//go->AddComponent(scoreComponent);
	//InputManager::GetInstance().AddCommand(SDL_SCANCODE_1, ExecuteType::Pressed, std::make_shared<DamageCommand>(go,1));
	//InputManager::GetInstance().AddCommand(ControllerButton::ButtonA, ExecuteType::Pressed, std::make_shared<DamageCommand>(go,1));
	//

	//auto hud = HudManager::GetInstance().CreateHud();
	//
	//auto go2 = std::make_shared<GameObject>(glm::vec3(100.f, 25.f, 0.f));
	//auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	//auto scorep1 = std::make_shared <TextComponent>(go2, " score p1", font, glm::tvec3<uint8_t> { 255, 255, 0 },glm::vec3(100.f, 25.f, 0.f));
	//go2->AddComponent(scorep1);
	//auto healthp1 = std::make_shared <TextComponent>(go2, " health p1", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(100.f, 25.f, 0.f));
	//go2->AddComponent(healthp1);
	//auto observer1 = std::make_shared <ObserverComponent>(go2,std::make_shared<PlayerObserver>());
	//subj1->AddObserver(observer1);
	//go2->AddComponent(observer1);
	//
	//InputManager::GetInstance().AddCommand(SDL_SCANCODE_2, ExecuteType::Pressed, std::make_shared<ScoreCommand>(scoreComponent, 1));


	//hud->AddComponent(std::make_shared<HudRenderComponent>(hud));
	//auto scoreHud1 = hud->AddComponent(std::make_shared<HudTextComponent>(hud," score p1", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(100.f, 25.f, 0.f), "player1 Score:"));
	//auto healthHud1 =hud->AddComponent(std::make_shared<HudTextComponent>(hud," Health p1", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(100.f, 5.f, 0.f), "player1 Health:"));

	//scorep1->SetHudElement(static_pointer_cast<HudTextComponent>(scoreHud1));
	//healthp1->SetHudElement(static_pointer_cast<HudTextComponent>(healthHud1));
	//scene.Add(go2);
	//scene.Add(go);
	//
	////Player2


	//go = std::make_shared<GameObject>(glm::vec3(100.f, 5.f, 0.f));


	//go->AddComponent(txt);
	//go->AddComponent(std::make_shared <HealthComponent>(go, 10));
	//subj1 = std::make_shared <SubjectComponent>(go);
	//go->AddComponent(subj1);
	//scoreComponent = std::make_shared <ScoreComponent>(go);
	//go->AddComponent(scoreComponent);
	//InputManager::GetInstance().AddCommand(SDL_SCANCODE_3, ExecuteType::Pressed, std::make_shared<DamageCommand>(go, 1));


	//hud = HudManager::GetInstance().CreateHud();

	//go2 = std::make_shared<GameObject>(glm::vec3(100.f, 25.f, 0.f));
	//font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	//scorep1 = std::make_shared <TextComponent>(go2, " score p2", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(100.f, 25.f, 0.f));
	//go2->AddComponent(scorep1);
	//healthp1 = std::make_shared <TextComponent>(go2, " health p2", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(100.f, 25.f, 0.f));
	//go2->AddComponent(healthp1);
	//observer1 = std::make_shared <ObserverComponent>(go2, std::make_shared<PlayerObserver>());
	//subj1->AddObserver(observer1);
	//go2->AddComponent(observer1);

	//InputManager::GetInstance().AddCommand(SDL_SCANCODE_4, ExecuteType::Pressed, std::make_shared<ScoreCommand>(scoreComponent, 1));


	//hud->AddComponent(std::make_shared<HudRenderComponent>(hud));
	//scoreHud1 = hud->AddComponent(std::make_shared<HudTextComponent>(hud, " score p2", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(300, 25.f, 0.f), "player2 Score:"));
	//healthHud1 = hud->AddComponent(std::make_shared<HudTextComponent>(hud, " Health p2", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(300, 5.f, 0.f), "player2 Health:"));

	//scorep1->SetHudElement(static_pointer_cast<HudTextComponent>(scoreHud1));
	//healthp1->SetHudElement(static_pointer_cast<HudTextComponent>(healthHud1));
	//scene.Add(go2);
	//scene.Add(go);



	//ServiceLocator::RegisterSoundSystem(new SDLMixerSoundSystem{ false });
	//SDLMixerSoundSystem* temp = static_cast<SDLMixerSoundSystem*>(ServiceLocator::GetSoundSystem());
	//
	//temp->AddSound("../Resources/Pokemon_DAEStyle.wav");
	//
	//InputManager::GetInstance().AddCommand(SDL_SCANCODE_P, ExecuteType::Pressed, std::make_shared<PlayCommand>(SoundID(0), 100.f));
	//temp->Play(0, 100);
	
	
}

void Minigin::Cleanup()
{
	UserCleanUp();
	Renderer::GetInstance().Destroy();
	delete m_Quit;
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
	ServiceLocator::DeleteSoundSystem();
}

void Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("Resources/");

	//InputManager::GetInstance().AddCommand(SDL_SCANCODE_0, ExecuteType::Released, std::make_shared<QuitCommand>(quit));

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& hudManager = HudManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto lastTime = high_resolution_clock::now();

		bool doContinue = true;

		while (doContinue&&!*m_Quit)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = duration<float>(currentTime - lastTime).count();
			UserUpdate(deltaTime);
			lastTime = currentTime;
			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			hudManager.Update(deltaTime);
			renderer.Render();
			
			//auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			//this_thread::sleep_for(sleepTime);
		}
	}


	Cleanup();
}

void Minigin::UserInitialize()
{
}

void Minigin::UserLoadGame() const
{
}

void Minigin::UserUpdate(float)
{
}

void Minigin::UserCleanUp()
{
}

void Minigin::Quit()
{
	*m_Quit=true;
}

