#include "QBertPCH.h"
#include "QBertGameApplication.h"
#include "QbertCommands.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "GridComponent.h"
#include "InputManager.h"


void QBertGameApplication::UserLoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("QbertScene");
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared <TextureComponent>(go, "background.jpg"));
	go->AddComponent(std::make_shared <RenderComponent>(go));
	scene.Add(go);
	CreateBlocks(scene);
	auto qbert =CreateQBert(scene);

	InputManager::GetInstance().AddCommand(SDL_SCANCODE_KP_1, ExecuteType::Pressed, std::make_shared<MoveLeftDown>(qbert,m_PosFix));
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_KP_3, ExecuteType::Pressed, std::make_shared<MoveRightDown>(qbert,m_PosFix));
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_KP_7, ExecuteType::Pressed, std::make_shared<MoveLeftUp>(qbert,m_PosFix));
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_KP_9, ExecuteType::Pressed, std::make_shared<MoveRightUp>(qbert,m_PosFix));
}

void QBertGameApplication::UserCleanUp()
{
}

void QBertGameApplication::CreateBlocks(Scene& scene)const
{


	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	int locationCounter = 0;
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j <= i; j++)
		{
			if (i % 2 == 1)
			{

				go = std::make_shared<GameObject>();
				auto pos = glm::vec3(m_Offset.x + (j - i / 2) * m_BlockSize.x - m_BlockSize.x / 2, m_Offset.y + i * m_BlockSize.y, 0);
				go->AddComponent(std::make_shared <TextureComponent>(go, "Cube1.png", pos));
				go->AddComponent(std::make_shared <RenderComponent>(go));
				go->AddComponent(std::make_shared <GridComponent>(go,28,m_BlockSize,glm::ivec2{j,i},m_Offset));
				scene.Add(go);
			}
			else
			{
				go = std::make_shared<GameObject>();
				auto pos = glm::vec3(m_Offset.x + (j - i / 2) * m_BlockSize.x , m_Offset.y + i * m_BlockSize.y, 0);
				go->AddComponent(std::make_shared <TextureComponent>(go, "Cube1.png", pos));
				go->AddComponent(std::make_shared <RenderComponent>(go));
				go->AddComponent(std::make_shared <GridComponent>(go, 28, m_BlockSize, glm::ivec2{ j,i }, m_Offset));
				scene.Add(go);
			}
			locationCounter++;
		}
	}
}

std::shared_ptr<GameObject> QBertGameApplication::CreateQBert(Scene& scene) const
{
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go = std::make_shared<GameObject>();

	auto pos = glm::vec3{ m_Offset.x + m_PosFix.x , m_Offset.y  + m_PosFix.y, 0 };
	go->AddComponent(std::make_shared <TextureComponent>(go, "tempQbert.png",pos ));
	go->AddComponent(std::make_shared <RenderComponent>(go));
	go->AddComponent(std::make_shared <GridComponent>(go, 28, m_BlockSize, glm::ivec2{ 0,0 }, m_Offset));
	scene.Add(go);
	return go;
}
